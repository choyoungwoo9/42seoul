#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 소켓 생성
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // 서버 주소 설정
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // 소켓에 주소 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind." << std::endl;
        close(serverSocket);
        return 1;
    }

    
    // 클라이언트 연결 대기
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server started. Waiting for client connections..." << std::endl;

    // 클라이언트 연결 수락
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept connection." << std::endl;
        close(serverSocket);
        return 1;
    }

    // 클라이언트 연결 성공
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
    std::cout << "Client connected from " << clientIP << std::endl;

    // 클라이언트에 메시지 전송
    const char* message = "Hello, client!";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Failed to send message to client." << std::endl;
    }

    // 클라이언트로부터 메시지 수신
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive message from client." << std::endl;
    } else {
        std::cout << "Received from client: " << buffer << std::endl;
    }

    // 연결 종료
    close(clientSocket);
    close(serverSocket);

    return 0;
}