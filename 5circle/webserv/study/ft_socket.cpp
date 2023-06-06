#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Failed to create socket");
        return 1;
    }
    std::cout << sockfd << std::endl;
    // 소켓 생성 성공, 이후 작업 수행

    return 0;
}