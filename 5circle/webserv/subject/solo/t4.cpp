#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEFAULT_PORT 8081
#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

using namespace std;

typedef struct
{
	int fd;
}	client_t;

void set_nonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void handle_request(client_t *client){
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read = read(client->fd, buffer, BUFFER_SIZE);
	if(bytes_read > 0)
	{
		const char* response = "HTTP/1.1 200 OK\r\n"
								"Content-Type: text/plain\r\n"
								"Content-Length: 13\r\n"
								"\r\n"
								"Hello, World!";
		write(client->fd, response, strlen(response));
	}
	else if(bytes_read == 0){
		close(client->fd);
		free(client);
	}	else{
		perror("read error");
		close(client->fd);
		free(client);
	}

}

int main()
{
    int server_fd;
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);

	//tcp요청을 처리할수있는 소켓 할당받음
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	//binding을 할 소켓 
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(DEFAULT_PORT);

	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	set_nonblocking(server_fd);

	if(listen(server_fd, SOMAXCONN) < 0)
	{
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", DEFAULT_PORT);

	int kq = kqueue();
	if(kq < 0)
	{
		perror("kqueue failed");
		exit(EXIT_FAILURE);
	}

	struct kevent change_list;
	struct kevent event_list[MAX_EVENTS];

	EV_SET(&change_list, server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

	if(kevent(kq, &change_list, 1, NULL, 0, NULL) < 0)
	{
		perror("Kevent failed");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		int nevents = kevent(kq, NULL, 0, event_list, MAX_EVENTS, NULL);
		if(nevents < 0)
		{
			perror("Kevent failed");
			exit(EXIT_FAILURE);
		}

		for(int i = 0; i < nevents; i ++)
		{
			int fd = event_list[i].ident;
			if(fd == server_fd)
			{
				if(event_list[i].filter == EVFILT_READ)
				{
					int client_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen);
					if(client_fd < 0){
						perror("Accpet failed");
						exit(EXIT_FAILURE);
					}

					set_nonblocking(client_fd);
					EV_SET(&change_list, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					if(kevent(kq, &change_list, 1, NULL, 0, NULL) < 0){
						perror("Kevent failed");
						exit(EXIT_FAILURE);
					}
				}
			}
			else
			{
				if(event_list[i].filter == EVFILT_READ)
				{
					client_t* client = (client_t*)malloc(sizeof(client_t));
					client->fd = fd;
					handle_request(client);
				}
			}
		}
	}
}