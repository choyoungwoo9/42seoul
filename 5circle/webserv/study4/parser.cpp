#include <unistd.h>
#include <fcntl.h>
#include <iostream>

using namespace std;



int main()
{
	int fd = open("config", O_RDONLY);
	char buf[10000];
	int length = read(fd, buf, sizeof(buf));
	buf[length] = '\0';
	cout << buf << endl;
	tokenizer();
}