#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main()
{
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1)
	{
		cout << "socket error" << endl;
		return 1;
	}
	char *port = "5000";
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		cout << "bind error" << endl;
		return 1;
	}
}