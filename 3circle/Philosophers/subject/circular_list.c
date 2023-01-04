/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:45:47 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/04 18:32:07 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include ""

//시작하면 먹으려고구 함
//먹는게 끝나면 포크를 놓고 자기 시작함
//자는게 끝나면 생각함
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_philo_and_fork
{
	int id;
	pthread_mutex_t *fork_mutex;
	struct s_philo_and_fork *prev;
	struct s_philo_and_fork *next;
}	t_philo_and_fork;

typedef struct s_dinner_info
{
	t_philo_and_fork *leader;
	int member_count;
}	t_dinner_info;

void make_list(int philo_count, t_philo_and_fork **leader)
{
	int i = 0;
	t_philo_and_fork *philo;
	t_philo_and_fork *fork;
	t_philo_and_fork *tmp;
	while(++i <= philo_count)
	{
		philo = malloc(sizeof(t_philo_and_fork));
		fork = malloc(sizeof(t_philo_and_fork));
		if(i == 1)
			*leader = philo;
		else
		{
			tmp->next = philo;
			philo->prev = tmp;
		}
		if(i == philo_count)
		{
			fork->next = *leader;
			(*leader)->prev = fork;
		}
		philo->id = i;
		philo->next = fork;
		fork->id = 0;
		fork->prev = philo;
		fork->fork_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork->fork_mutex, NULL);
		pthread_mutex_unlock(fork->fork_mutex);
		tmp = fork;
	}
}

void *philo_start(t_philo_and_fork *philo)
{
	return NULL;
}

int main()
{
	int philo_count = 5;
	t_dinner_info info;
	info.member_count = philo_count;
	make_list(info.member_count, &info.leader);
	int i = 0;
	t_philo_and_fork *tmp_philo = info.leader;
	while(++ i < 5)
	{
		pthread_t thread_t;
		pthread_create(&thread_t, NULL, philo_start, tmp_philo);
		tmp_philo = tmp_philo->next;
	}
	while(1)
	{
		
	}
}
