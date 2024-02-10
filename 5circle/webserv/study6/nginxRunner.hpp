#ifndef NGINX_RUNNER_HPP
#define NGINX_RUNNER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "nginxConfig.hpp"

void handleError(std::string errMsg)
{
	fprintf(stderr, "오류 발생: %s\n", strerror(errno));
	std::cout << errMsg << std::endl;
	exit(1);
}

void makeNonBlock(int fd)
{
	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) == -1)
		handleError("fcntl Error");
}

sockaddr_in makeTCPSocketAddr(std::string host, int port)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	// 추후 getaddrInfo로 변경 -> 서브젝트
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	return addr;
}

static Context &findHttpServer(Context &mainContext)
{
	for (int i = 0; i < mainContext.subContextVector.size(); i++)
	{
		if (mainContext.subContextVector[i].type.compare(CONTEXT_HTTP) == 0)
			return mainContext.subContextVector[i];
	}
	return mainContext;
}

// 목표 nginx룰에 따라 파일을 서빙하는 GET전용 서버 프로그램 만들기
// 1. nginxConfig에 명시된 port를 여는 프로그램 만들기
// port가 key인 map열고, 안에 value로 서버저장 0.0.0.0있나 확인하고, 있으면
// 일단 열어놓고, 서버이름, 포트 매핑해놓는다. 이후 요청들어오면, 그떄 생각하자.
class NginxRunner
{
public:
	NginxRunner(Context &mainContext) : mainContext(mainContext){};
	void run()
	{
		listenAllAddressAndSetupMap();
		kqueueFd = kqueue();
		// listen하고 있는 소켓을 kqueue에 등록
		std::map<int, std::pair<std::string, int>>::iterator it;
		for (it = listenerFdToAddressMap.begin(); it != listenerFdToAddressMap.end(); it++)
		{
			int socketFd = it->first;
			struct kevent tempEvent;
			EV_SET(&tempEvent, socketFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
			changeList.push_back(tempEvent);
		}
		while (1)
		{
			// 이번에 등록할 이벤트인 changeList 등록, 새로운 이벤트는 changeList에 등록됨
			// 20 하드코딩 제거, //timeoutNULL이면 blocking아닌지 추후 확인
			int newEventSize = kevent(kqueueFd, &changeList[0], changeList.size(), eventList, 20, NULL);
			if (newEventSize == -1)
				handleError("kevent");
			changeList.clear();
			for (int i = 0; i < newEventSize; i++)
			{
				struct kevent *curEvent = &eventList[i];
				// if(curEvent->)
			}
		}
	}

private:
	// fd listenAddress(host port) map
	std::map<int, std::pair<std::string, int>> listenerFdToAddressMap;
	Context &mainContext;
	// kqueue의 Fd
	int kqueueFd;
	// kqueue에 등록하고 싶은 이벤트들을 담아놓는는 리스트
	std::vector<struct kevent> changeList;
	// kqueue 루틴 안에서 일어난 이벤트들이 event_list 배열에 담긴다.
	struct kevent eventList[20];
	// void initKqueue()
	// {
	// }
	// int registerListenSocketToKqueue()
	// {
	// 	int kqueueFd = kqueue();
	// }
	void listenAllAddressAndSetupMap()
	{
		Context &httpContext = findHttpServer(mainContext);
		// std::cout << httpContext.type << std::endl;
		if (httpContext.type.compare(CONTEXT_HTTP) != 0)
			return;
		std::set<std::pair<std::string, int>> addressSet;
		for (int i = 0; i < httpContext.subContextVector.size(); i++)
		{
			Context &serverContext = httpContext.subContextVector[i];
			std::pair<std::string, int> addressPair = std::pair<std::string, int>(serverContext.listenD.host, serverContext.listenD.port);
			// 이미 열어놓는 주소면 지나간다.
			if (addressSet.find(addressPair) != addressSet.end())
				continue;
			addressSet.insert(addressPair);
			// std::cout << "ADDRESS : " << serverContext.listenD.host << ":" << serverContext.listenD.port << std::endl;

			int socketFd = socket(PF_INET, SOCK_STREAM, 0);
			if (socketFd == -1)
				handleError("socket Error");
			listenerFdToAddressMap[socketFd] = addressPair;

			// reuse 처리 -> 추후 주석
			int reuse = 1;
			if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
				handleError("setsockopt(SO_REUSEADDR) failed");
			makeNonBlock(socketFd);
			if (listen(socketFd, 4096) == -1)
				handleError("listen Error");
		}
	};
};

#endif