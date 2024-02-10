#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define SERVER_NAME "127.0.0.1"

void handleError(std::string errMsg)
{
	std::cout << errMsg << std::endl;
	exit(1);
}

int main()
{
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_NAME);
	serverAddr.sin_port = htons(12345);
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1)
		handleError("socket");

	if (connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
		handleError("connect");
	printf("success\n");
	write(socketFd, "abc", 4);
	// sleep(1);
	char buf[400];
	if (read(socketFd, buf, 400) == -1)
	{
		std::cout << "READ ERROR" << std::endl;
		return 1;
	}
	std::cout << buf << std::endl;
	close(socketFd);
}