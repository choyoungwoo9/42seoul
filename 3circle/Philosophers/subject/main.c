/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/04 19:05:06 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

int mail = 0;
pthread_mutex_t mutex;

void *func(void *alpha)
{
	printf("%s\n", (char *)alpha);
	pthread_mutex_lock(&mutex);
	for(int i = 0; i < 100; i ++)
		mail ++;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(int argc, char **argv)
{
	char *phil_num = argv[1];
	char *time_to_die = argv[2];
	char *time_to_sleep = argv[3];
	char *phil_must_eat = argv[4];
	pthread_t thread1;
	pthread_t thread2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, func, "thread1");
	pthread_create(&thread2, NULL, func, "thread2");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", mail);
}