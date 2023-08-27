#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT (7777)
#define BUFF_SIZE (1024)
#define QUEUE_LIMIT (1)

int main()
{
	int serverSocket;
	struct sockaddr_in serverAddr;
	int clientSocket;
	struct sockaddr_in clientAddr;
	unsigned int clientAddrLength;
	char buff[BUFF_SIZE];

	printf("Server start\n");
	if((serverSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket fail\n");
		return -1;
	}
	memset(&serverAddr, 0x00, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	if(bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("bind() failed\n");
		return -1;
	}
	if(listen(serverSocket, QUEUE_LIMIT) < 0)
	{
		printf("liten() failed.\n");
		return -3;
	}

	clientAddrLength = sizeof(clientAddr);
	while(1)
	{
		clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLength);
		if(clientSocket > 0)
		{
			break;
		}
	}
	printf("	Client is connected\n");
	recv(clientSocket, buff, BUFF_SIZE, 0);
	printf("Recv data : %s\n", buff);
	close(clientSocket);
	close(serverSocket);
	printf("End\n");
}
