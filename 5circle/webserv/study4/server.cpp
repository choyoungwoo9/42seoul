#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <vector>
#include <map>
#include <string>
#include <sys/stat.h>
#include "httpParser.cpp"

void handleError(std::string errMsg)
{
	fprintf(stderr, "오류 발생: %s\n", strerror(errno));
	std::cout << errMsg << std::endl;
	exit(1);
}

void makeNonBlock(int fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		handleError("fcntl Error");
}

int isReadableRegularFile(std::string path)
{
	struct stat statbuf;

	// 파일이 읽기 가능한지 확인
	if (access(path.c_str(), R_OK) != 0)
	{
		return 0; // 읽기 권한 없음
	}

	// 파일 타입 확인
	if (stat(path.c_str(), &statbuf) != 0)
	{
		return 0; // stat 호출 실패
	}
	return S_ISREG(statbuf.st_mode);
}

// 목표 : 파일을 서빙하는 GET전용 서버 프로그램 만들기
// 목표 2 : keep-alive이며, timeout이 없는 GET전용 리소스낭비 갑 GET전용 프로그램 만들기
int main()
{
	int socketFd = socket(PF_INET, SOCK_STREAM, 0);
	int reuse = 1;
	// reuse 처리
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
		handleError("setsockopt(SO_REUSEADDR) failed");
	makeNonBlock(socketFd);
	// printf("%d\n", fcntl(socketFd, F_GETFL) | O_NONBLOCK);
	if (socketFd == -1)
		handleError("socket Error");
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socketFd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		handleError("bind Error");
	if (listen(socketFd, 100) == -1)
		handleError("listen Error");

	int kqueueFd = kqueue();
	// fcntl Error
	//  makeNonBlock(kqueueFd);
	std::vector<struct kevent> change_list;

	struct kevent temp_event;
	EV_SET(&temp_event, socketFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	change_list.push_back(temp_event);

	std::map<int, http> clients;
	std::map<int, int> clientFileMap;
	int new_events;
	struct kevent event_list[8];
	try
	{
		while (1)
		{
			new_events = kevent(kqueueFd, &change_list[0], change_list.size(), event_list, 8, NULL);
			if (new_events == -1)
				handleError("kevent");
			change_list.clear();
			for (int i = 0; i < new_events; i++)
			{
				struct kevent *curr_event = &event_list[i];
				if (curr_event->flags == EV_ERROR)
				{
					std::cerr << "Write error: " << strerror(errno) << std::endl;
					if (curr_event->ident == socketFd)
						handleError("server socket error");
					else
					{
						printf("client socket error\n");
						close(curr_event->ident);
					}
				}
				else if (curr_event->filter == EVFILT_READ)
				{
					// std::cout << curr_event->ident << " result : " << (clients.find(curr_event->ident) != clients.end()) <<" here\n";
					// listen하고 있는 소켓에 이벤트 발생
					if (curr_event->ident == socketFd)
					{
						int clientSocket = accept(socketFd, NULL, NULL);
						makeNonBlock(clientSocket);
						EV_SET(&temp_event, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
						change_list.push_back(temp_event);
						clients[clientSocket] = http();
					}
					else if (clients.find(curr_event->ident) != clients.end()) // 클라이언트 소켓에 읽기 이벤트 발생
					{
						char buf[1000];
						int n = read(curr_event->ident, buf, sizeof(buf));
						// 이거 다른 방식으로 바꿔야 할듯
						if (n == 0) // 클라이언트가 연결을 종료시켰을때
						{
							close(curr_event->ident);
							clients.erase(curr_event->ident);
							std::cout << "client disconnect " << curr_event->ident << "\n";
							break;
						}
						// printf("here1\n");
						clients[curr_event->ident].addReqMsg(std::string(buf, n));
						// printf("here2\n");
						// std::cout << "received : " << curr_event->ident << std::endl;
						if (clients[curr_event->ident].isHeadEnd)
						{
							clients[curr_event->ident].print();
							int fileFd;
							if (isReadableRegularFile("static/" + clients[curr_event->ident].target))
							{
								fileFd = open(std::string("static/" + clients[curr_event->ident].target).c_str(), O_RDONLY);
								if (fileFd == -1)
									fileFd = open("static/404.html", O_RDONLY);
							}
							else
								fileFd = open("static/404.html", O_RDONLY);
							makeNonBlock(fileFd);
							// 파일 FD와 클라이언트를 매핑
							// 나중에 구현할때 set mimetime이게 필요할듯
							// url != 파일 이름이니까 실제 파일이름을 저장하는 로직도 필요할듯?
							clientFileMap[fileFd] = curr_event->ident;
							if (clients[curr_event->ident].target.find(".html") != std::string::npos)
								clients[curr_event->ident].response = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\n\n";
							else if (clients[curr_event->ident].target.find(".css") != std::string::npos)
								clients[curr_event->ident].response = "HTTP/1.1 200 OK\nContent-Type: text/css; charset=utf-8\n\n";
							else if (clients[curr_event->ident].target.compare("/favicon.ico") == 0)
								clients[curr_event->ident].response = "HTTP/1.1 200 OK\nContent-Type: image/x-icon\n\n";
							else
								clients[curr_event->ident].response = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\n\n";
							// clients[curr_event->ident].response = "HTTP/1.1 200 OK\nContent-Type: text/plain; charset=utf-8\n\n";
							EV_SET(&temp_event, fileFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
							kevent(kqueueFd, &temp_event, 1, NULL, 0, NULL);

							EV_SET(&temp_event, curr_event->ident, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
							kevent(kqueueFd, &temp_event, 1, NULL, 0, NULL);
							// clients[curr_event->ident].response = clients[curr_event->ident].makeHeader();
							// std::cout << clients[curr_event->ident].response << "\n";
						}
					}
					else if (clientFileMap.find(curr_event->ident) != clientFileMap.end())
					{
						// std::cout << "readFile\n";
						int clientFd = clientFileMap[curr_event->ident];
						char buf[1000];
						int readLength = read(curr_event->ident, buf, sizeof(buf));
						if (readLength > 0)
						{
							clients[clientFd].response.append(buf, readLength);
							// std::cout << clients[clientFd].response << std::endl;
						}
						else
						{ // 실패 처리
						}
						if (curr_event->data <= sizeof(buf))
						{
							clients[clientFd].isFileEnd = true;
							close(curr_event->ident);
							clientFileMap.erase(curr_event->ident);
						}
					}
				}
				else if (curr_event->filter == EVFILT_WRITE)
				{
					// std::cout << curr_event->ident << " result : " << (clients.find(curr_event->ident) != clients.end()) << " here\n";
					// std::cout << clients[curr_event->ident].target << std::endl;
					if (clients.find(curr_event->ident) != clients.end())
					{
						int writeLength = write(curr_event->ident, clients[curr_event->ident].response.data(), clients[curr_event->ident].response.size());
						// std::cout << writeLength << std::endl;
						if (writeLength == -1) // 오류처리
						{
							std::cerr << "Write error: " << strerror(errno) << std::endl;
							// write(1, "쓰기오류", 2);
							// exit(1);
						}
						clients[curr_event->ident].response = clients[curr_event->ident].response.substr(writeLength, clients[curr_event->ident].response.length() - writeLength);
						if (clients[curr_event->ident].response.empty() && clients[curr_event->ident].isFileEnd)
						{
							EV_SET(&temp_event, curr_event->ident, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
							// std::cout << "close" << std::endl;
							kevent(kqueueFd, &temp_event, 1, NULL, 0, NULL);
							// keep-alive일때 아껴놓는다?
							// 그런데 닫았는데 어떻게 요청이 계속 지속되는걸까..
							// 크롬이 알아서 한다 ! 
							//닫히면, 다시 요청을 보내 accept된다.
							close(curr_event->ident);
							clients.erase(curr_event->ident); // 클라이언트 관리 목록에서 제거
						}
					}
				}
			}
		}
	}
	catch (std::exception e)
	{
		handleError("a");
	}
	return 0;
}