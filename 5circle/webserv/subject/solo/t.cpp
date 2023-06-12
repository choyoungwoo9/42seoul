#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEFAULT_PORT 8082
#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

using namespace std;

typedef struct {
    int fd;
} client_t;

void set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void handle_request(client_t* client) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client->fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        // 수신한 데이터 처리
        // 예: HTTP 요청 처리

        // 응답 데이터 전송
        const char* response = "HTTP/1.1 200 OK\r\n"
                               "Content-Type: text/plain\r\n"
                               "Content-Length: 13\r\n"
                               "\r\n"
                               "Hello, World!";
        write(client->fd, response, strlen(response));
    } else if (bytes_read == 0) {
        // 연결이 닫힌 경우
        close(client->fd);
        free(client);
    } else {
        // 에러 발생
        perror("Read error");
        close(client->fd);
        free(client);
    }
}

int main() {
    int server_fd;
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);

    // 서버 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DEFAULT_PORT);

    // 포트에 바인딩
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 비동기 모드로 설정
    set_nonblocking(server_fd);

    // 연결 요청 수신 대기
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", DEFAULT_PORT);

    // kqueue 생성
    int kq = kqueue();
    if (kq < 0) {
        perror("Kqueue failed");
        exit(EXIT_FAILURE);
    }

    struct kevent change_list;
    struct kevent event_list[MAX_EVENTS];

    // 서버 소켓에 대한 이벤트 등록
    EV_SET(&change_list, server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    // kqueue에 이벤트 등록
    if (kevent(kq, &change_list, 1, NULL, 0, NULL) < 0) {
        perror("Kevent failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int nevents = kevent(kq, NULL, 0, event_list, MAX_EVENTS, NULL);
        if (nevents < 0) {
            perror("Kevent failed");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nevents; i++) {
            int fd = event_list[i].ident;

            if (fd == server_fd) {
                // 서버 소켓에 이벤트 발생한 경우
                if (event_list[i].filter == EVFILT_READ) {
                    // 연결 요청 수락
                    int client_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen);
                    if (client_fd < 0) {
                        perror("Accept failed");
                        exit(EXIT_FAILURE);
                    }

                    // 클라이언트 소켓을 비동기 모드로 설정
                    set_nonblocking(client_fd);

                    // 클라이언트 소켓에 대한 이벤트 등록
                    EV_SET(&change_list, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

                    // kqueue에 이벤트 등록
                    if (kevent(kq, &change_list, 1, NULL, 0, NULL) < 0) {
                        perror("Kevent failed");
                        exit(EXIT_FAILURE);
                    }
                }
            } else {
                // 클라이언트 소켓에 이벤트 발생한 경우
                if (event_list[i].filter == EVFILT_READ) {
                    client_t* client = (client_t*)malloc(sizeof(client_t));
                    client->fd = fd;

                    // 클라이언트 요청 처리
                    handle_request(client);
                }
            }
        }
    }

    return 0;
}
