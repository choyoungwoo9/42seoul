#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/event.h>
#include <fcntl.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength;
    int kq;
    struct kevent events[MAX_EVENTS];
    char buffer[BUFFER_SIZE];

    // 서버 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(80);

    // 소켓과 주소 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // 연결 대기 상태로 전환
    if (listen(serverSocket, SOMAXCONN) == -1) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    // kqueue 생성
    kq = kqueue();
    if (kq == -1) {
        perror("Failed to create kqueue");
        exit(EXIT_FAILURE);
    }

    // 서버 소켓을 kqueue에 등록
    struct kevent serverEvent;
    EV_SET(&serverEvent, serverSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
    if (kevent(kq, &serverEvent, 1, NULL, 0, NULL) == -1) {
        perror("Failed to register server socket event");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for connections...\n");

    while (1) {
        // 이벤트 대기
        int numEvents = kevent(kq, NULL, 0, events, MAX_EVENTS, NULL);
        if (numEvents == -1) {
            perror("Failed to wait for events");
            exit(EXIT_FAILURE);
        }

        // 발생한 이벤트 처리
        for (int i = 0; i < numEvents; i++) {
            int fd = events[i].ident;
            int filter = events[i].filter;

            // 새로운 연결 수신
            if (fd == serverSocket && filter == EVFILT_READ) {
                clientAddressLength = sizeof(clientAddress);
                clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
                if (clientSocket == -1) {
                    perror("Failed to accept client connection");
                    exit(EXIT_FAILURE);
                }

                printf("New client connected: %s\n", inet_ntoa(clientAddress.sin_addr));

                // 클라이언트 소켓을 kqueue에 등록
                struct kevent clientEvent;
                EV_SET(&clientEvent, clientSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
                if (kevent(kq, &clientEvent, 1, NULL, 0, NULL) == -1) {
                    perror("Failed to register client socket event");
                    exit(EXIT_FAILURE);
                }
            }
            // 데이터 수신
            else if (filter == EVFILT_READ) {
                memset(buffer, 0, BUFFER_SIZE);
                ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
                if (bytesRead == -1) {
                    perror("Failed to read data from client");
                    exit(EXIT_FAILURE);
                } else if (bytesRead == 0) {
                    printf("Client disconnected\n");
                    close(fd);
                } else {
                    printf("Received data from client: %s\n", buffer);

                    // 받은 데이터를 그대로 클라이언트에게 전송
                    ssize_t bytesWritten = write(fd, buffer, bytesRead);
                    if (bytesWritten == -1) {
                        perror("Failed to write data to client");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    // kqueue 및 소켓 종료
    close(kq);
    close(serverSocket);

    return 0;
}
