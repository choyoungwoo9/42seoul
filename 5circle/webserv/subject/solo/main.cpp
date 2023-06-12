//요청을 받으면 정적인 응답 리턴하는 페이지 만들자
//모두 non block으로 구성하자
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <string>

using namespace std;
#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

void set_nonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void handle_request(int fd)
{
	const char* response = "HTTP/1.1 200 OK\r\n"
								"Content-Type: text/plain\r\n"
								"Content-Length: 13\r\n"
								"\r\n"
								"Hello, World!";
	char buffer[BUFFER_SIZE];
	string str;
	// while(1)
	// {
		ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
		if(bytes_read > 0)
		{
			buffer[bytes_read] = 0;
			str += buffer;
			write(fd, response, strlen(response));
		}
		else if(bytes_read == 0)
		{
			cout << str;
			close(fd);
			//break;
		}
		else
		{
			perror("read error");
			close(fd);
			//break;
		}
	//}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		cout << "one arg plz\n";
		exit(EXIT_FAILURE);
	}
	int server_fd;
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(atoi(argv[1]));
	int addrlen = sizeof(server_addr);

	if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	set_nonblocking(server_fd);

	if(listen(server_fd, SOMAXCONN) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	cout << "Server listening on port "<< atoi(argv[1]) << endl;
	
	struct kevent change_list;
	struct kevent event_list[MAX_EVENTS];
	//EVFILT_READ로 등록한 이벤트는 읽을수있게 되었다 -> 입력버퍼에 뭐가 들어왔다.
	EV_SET(&change_list, server_fd, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR, 0, 0, NULL);
	int kq = kqueue();
	if(kq < 0)
	{
		perror("kqueue error");
		exit(EXIT_FAILURE);
	}

	//각 매개변수는 kqueue 디스크립터 변수, 등록할 이벤트배열, 등록할 이벤트의 개수
	//이벤트를 받을수있는 배열, 이벤트를 받을수있는 배열의 수, 타임아웃을 의미한다
	//nevent가 0이면 listen하고 있는 이벤트가 없는것이므로 timeout과 관계없이 바로 리턴된다
	if(kevent(kq, &change_list, 1, NULL, 0, NULL) < 0)
	{
		perror("kevent error");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		//일어난 이벤트의 수를 리턴
		int nevents = kevent(kq, NULL, 0, event_list, MAX_EVENTS, NULL);
		if(nevents < 0)
		{
			perror("Kevent failed");
			exit(EXIT_FAILURE);
		}

		for(int i = 0; i < nevents; i ++)
		{
			int fd = event_list[i].ident;
			//이벤트가 일어난 fd가 listen하고 있는 소켓일때
			if(fd == server_fd)
			{
				//이벤트의 종류가 읽을수있는 상태인것일때
				if(event_list[i].filter == EVFILT_READ)
				{
					int client_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t *)&addrlen);
					if(client_fd < 0)
					{
						perror("Accept failed");
						exit(EXIT_FAILURE);
					}
					set_nonblocking(client_fd);
					EV_SET(&change_list, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					if(kevent(kq, &change_list, 1, NULL, 0, NULL) < 0)
					{
						perror("Kevent failed");
						exit(EXIT_FAILURE);
					}
				}
			}
			else
			{
				if(event_list[i].filter == EVFILT_READ)
				{
					handle_request(fd);
				}
			}
		}
	}
}