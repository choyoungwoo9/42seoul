#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

void *thread_routine(void *data)
{

}

int main(void)
{
	pid_t i  = fork();
	if(i == 0)
	{
		while(1)
		{
			sleep(1);
			printf("here\n");
		}
	}
	printf("parant_start\n");
}
