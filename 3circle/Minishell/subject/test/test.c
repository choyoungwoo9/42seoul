#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char *arg;
int a;
int test2();

int main()
{
	a = 3;
	int pid = fork();
	if(pid == 0)
	{
		test2();
	}
	else
	{
		wait(NULL);
		printf("%d\n", a);
		printf("%s\n", arg);
	}
}