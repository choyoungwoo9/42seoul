/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start_dinner_do.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/14 10:33:56 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	eat_with_fork(t_thread_param *param, t_fork *first_fork,
	t_fork *second_fork);

int	eat(t_thread_param *param)
{
	t_table				*table;
	t_fork				*left_fork;
	t_fork				*right_fork;
	int					id;
	int					starve_count;

	table = param->table;
	pthread_mutex_lock(&table->philo->philo_mutex);
	id = table->philo->id;
	starve_count = table->philo->starve_count;
	pthread_mutex_unlock(&table->philo->philo_mutex);
	left_fork = table->prev->fork;
	right_fork = table->next->fork;
	if (id % 2)
	{
		usleep(10000);
		if(eat_with_fork(param, left_fork, right_fork))
			return -1;
	}
	else
	{
		// if (!starve_count % 2)
		// 	usleep(20);
		if(eat_with_fork(param, right_fork, left_fork))
			return -1;
	}
	return 0;
}

static int	eat_with_fork(t_thread_param *param,
	t_fork *first_fork, t_fork *second_fork)
{
	pthread_t	thread;

	pthread_mutex_lock(&(first_fork->fork_mutex));
	first_fork->fork_owner = param->table->philo->id;
	print_func(param->info, first_fork, "fork");
	pthread_mutex_lock(&(second_fork->fork_mutex));
	second_fork->fork_owner = param->table->philo->id;
	print_func(param->info, second_fork, "fork");
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	param->table->philo->starve_count ++;
	if(param->table->philo->state == DEAD_STATE)
	return -1;
	param->table->philo->state = EATING_STATE;
	print_func(param->info, param->table->philo, "state");
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	pthread_create(&thread, NULL, run_dead_timer_thread_func, (void *)param);
	pthread_detach(thread);
	usleep(param->info->time_to_eat * 1000);
	first_fork->fork_owner = 0;
	pthread_mutex_unlock(&(first_fork->fork_mutex));
	second_fork->fork_owner = 0;
	pthread_mutex_unlock(&(second_fork->fork_mutex));
	return (0);
}


int	sleep_and_think(t_thread_param *param)
{
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	if(param->table->philo->state == DEAD_STATE)
		return -1;
	param->table->philo->state = SLEEPING_STATE;
	print_func(param->info, param->table->philo, "state");
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	usleep(param->info->time_to_sleep * 1000);
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	if(param->table->philo->state == DEAD_STATE)
		return -1;
	param->table->philo->state = THINKING_STATE;
	print_func(param->info, param->table->philo, "state");
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	return 0;
}

