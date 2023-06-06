#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {

    const char* hostname = "www.naver.com";
    const char* service = "http";

    struct addrinfo hints{}, *result = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // 호스트 이름 및 서비스 이름으로 주소 정보 검색
    int status = getaddrinfo(hostname, service, &hints, &result);
    if (status != 0) {
        std::cerr << "Failed to get address info: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // 첫 번째 주소 정보에서 IP 주소 얻기
    struct sockaddr_in* address = reinterpret_cast<struct sockaddr_in*>(result->ai_addr);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address->sin_addr), ip, INET_ADDRSTRLEN);
    std::cout << "IP Address: " << ip << std::endl;

    // 주소 정보 해제
    freeaddrinfo(result);

    // 소켓 생성
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // 소켓 옵션 설정
    int reuse = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        std::cerr << "Failed to set socket option." << std::endl;
        close(socket_fd);
        return 1;
    }

    // 소켓 로컬 주소 조회
    struct sockaddr_in local_address{};
    socklen_t address_length = sizeof(local_address);
    if (getsockname(socket_fd, reinterpret_cast<struct sockaddr*>(&local_address), &address_length) == -1) {
        std::cerr << "Failed to get local address." << std::endl;
        close(socket_fd);
        return 1;
    }

    // 로컬 주소 출력
    char local_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(local_address.sin_addr), local_ip, INET_ADDRSTRLEN);
    std::cout << "Local IP Address: " << local_ip << std::endl;

    // 연결 종료
    close(socket_fd);

    return 0;
}
