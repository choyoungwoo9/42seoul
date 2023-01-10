#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

int count = 0;
pthread_mutex_t mutex;


//쓰레드가 하는 동작
void *take_fork(void *data)
{
	//pthread_mutex_lock(&mutex);
	sleep(1);
	count ++;
	(*(int *)data) ++;
	printf("data : %d\n", *(int *)data);
	//pthread_mutex_unlock(&mutex);
	return NULL;
}

int main()
{
	int a;
	pthread_t thread;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, take_fork, (void *)&a);
	//pthread_join(thread, NULL);
	pthread_detach(thread);
	printf("a : %d", a);
	return (0);
}
