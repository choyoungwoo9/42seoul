#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>


int main() {
    // 서버 소켓 생성 및 설정

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // ...

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Failed to bind");
        return 1;
    }

    if (listen(sockfd, 5) == -1) {
        perror("Failed to listen");
        return 1;
    }

    // 클라이언트의 연결을 수락

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd == -1) {
        perror("Failed to accept connection");
        return 1;
    }

    // 클라이언트와 통신

    // 데이터 수신
    char buffer[1024];
    ssize_t num_bytes = recv(newsockfd, buffer, sizeof(buffer), 0);
    // ...

    // 클라이언트와의 통신 종료
    close(newsockfd);

    return 0;
}