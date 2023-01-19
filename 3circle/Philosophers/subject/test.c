#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
int count = 0;

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>

void busy_sleep(unsigned long long sleep_us, struct timeval time)
{
	while(1)
	{
		struct timeval tmp_time;
		gettimeofday(&tmp_time, NULL);
		long long tmp_tmp_time = ((tmp_time.tv_sec - time.tv_sec) * 1000000 + (tmp_time.tv_usec - time.tv_usec));
		if(tmp_tmp_time > sleep_us)
			break;
	}
}

int main(int argc, char *argv[]) 
{
	struct timeval start_time;
	gettimeofday(&start_time, NULL);
	long long current_time;
	struct timeval time;
	while(1)
	{
		gettimeofday(&time, NULL);
		current_time = ((time.tv_sec - start_time.tv_sec) * 1000 + (time.tv_usec - start_time.tv_usec) / 1000);
		printf("cuurent : %lld\n", current_time);
		//usleep(1000 * 100);
		busy_sleep(1000 * 100, time);
	}
}
// Output: Done
