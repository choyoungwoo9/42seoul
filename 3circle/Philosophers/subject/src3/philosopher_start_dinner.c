/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start_dinner.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/09 12:03:59 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	*run_dead_timer_thread_func(void *param)
{
	usleep(((t_thread_param *)param)->info->time_to_die * 1000);
	(((t_thread_param *)param)->philo_and_fork->philo->dinner_count) ++;
	(((t_thread_param *)param)->philo_and_fork->philo->starve_count) --;
	if (((t_thread_param *)param)->philo_and_fork->philo->starve_count <= 0)
	{
		((t_thread_param *)param)->philo_and_fork->philo->state = DEAD_STATE;;
		print_philo_state(((t_thread_param *)param)->info, ((t_thread_param *)param)->philo_and_fork->philo);
	}
	return (NULL);
}

static void	*philo_routine(void *param)
{
	pthread_t thread_first;

	pthread_create(&thread_first, NULL, run_dead_timer_thread_func, param);
	((t_thread_param *)param)->philo_and_fork->philo->state = THINKING_STATE;
	print_philo_state(((t_thread_param *)param)->info,
		((t_thread_param *)param)->philo_and_fork->philo);
	while (1)
	{
		// if(((t_thread_param *)param)->philo_and_fork->philo->state == DEAD_STATE)
		// {
		// 	//free(param)
		// 	return NULL;
		// }
		eat((t_thread_param *)param);
		sleep_and_think((t_thread_param *)param);
	}
	return NULL;
}

static t_thread_param *set_param(t_dinner_info *info, t_philo_and_fork *philo_and_fork)
{
	t_thread_param *param;
	param = malloc(sizeof(t_thread_param));
	param->info = info;
	param->philo_and_fork = philo_and_fork;
	return param;
}

static void start_philo_thread(t_dinner_info *info)
{
	int i = 0;
	t_philo_and_fork *tmp;
	t_thread_param *param;
	tmp = info->leader;
	while(++ i <= info->phil_num)
	{
		if(i == 1)
			gettimeofday(&(info->start_time), NULL);
		param = set_param(info, tmp);
		pthread_create(&(tmp->philo->philo_thread), NULL, philo_routine, (void *)param);
		tmp = tmp->next->next;
	}
}

void start_dinner(t_dinner_info *info)
{
	pthread_mutex_init(&info->print_mutex, NULL);
	start_philo_thread(info);
}