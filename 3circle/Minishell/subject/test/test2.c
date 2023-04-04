#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern char *arg;
extern int a;

int test2()
{
	printf("%d\n", a);
	
	arg = malloc(sizeof(char *) * 2);
	arg[0] = 'A';
	arg[1] = '\0';
	printf("here\n");
	sleep(1);
	return 1;
}