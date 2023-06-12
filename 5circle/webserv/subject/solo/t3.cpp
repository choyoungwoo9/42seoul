#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/event.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    int kq, nev;
    struct kevent events[MAX_EVENTS];
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8082);

    // 소켓에 주소 연결
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // 소켓을 수동 대기 상태로 전환
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    // kqueue 생성
    if ((kq = kqueue()) == -1) {
        perror("kqueue");
        exit(1);
    }

    // 서버 소켓을 kqueue에 등록
	struct timespec timeout = {0, 0};  // 블로킹하지 않기 위해 timeout을 0으로 설정
    struct kevent ev;
    EV_SET(&ev, server_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    if (kevent(kq, &ev, 1, NULL, 0, &timeout) == -1) {
        perror("kevent");
        exit(1);
    }

    printf("Server started. Waiting for connections...\n");
    while (1) {
		printf("here\n");
        // 이벤트 대기
        nev = kevent(kq, NULL, 0, events, MAX_EVENTS, &timeout);
        if (nev == -1) {
            perror("kevent");
            exit(1);
        }

        // 이벤트 처리
        for (int i = 0; i < nev; ++i) {
            int fd = events[i].ident;
            int filter = events[i].filter;

            // 새로운 클라이언트 연결 수락
            if (fd == server_fd && filter == EVFILT_READ) {
                client_len = sizeof(client_addr);
                client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
                if (client_fd == -1) {
                    perror("accept");
                    exit(1);
                }
                printf("New connection accepted. Client: %s:%d\n",
                       inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                // 클라이언트 소켓을 kqueue에 등록
                struct kevent ev;
                EV_SET(&ev, client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                if (kevent(kq, &ev, 1, NULL, 0, NULL) == -1) {
                    perror("kevent");
                    exit(1);
                }
            }
            // 클라이언트로부터 데이터 수신 및 에코
            else if (filter == EVFILT_READ) {
                ssize_t num_bytes = recv(fd, buffer, sizeof(buffer), 0);
                if (num_bytes <= 0) {
                    // 클라이언트 연결 종료
                    close(fd);
                    printf("Connection closed. Client: %s:%d\n",
                           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                } else {
                    // 수신한 데이터 에코
                    if (send(fd, buffer, num_bytes, 0) == -1) {
                        perror("send");
                        exit(1);
                    }
                }
            }
        }
    }

    // kqueue 및 소켓 종료
    close(kq);
    close(server_fd);

    return 0;
}
