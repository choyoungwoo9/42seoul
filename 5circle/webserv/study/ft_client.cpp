#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 소켓 생성
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // 서버 주소 설정
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);

    // 서버에 연결
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to connect to server." << std::endl;
        close(clientSocket);
        return 1;
    }

    // 서버로부터 메시지 수신
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive message from server." << std::endl;
    } else {
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // 서버에 메시지 전송
    const char* message = "Hello, server!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Failed to send message to server." << std::endl;
    }

    // 연결 종료
    close(clientSocket);

    return 0;
}