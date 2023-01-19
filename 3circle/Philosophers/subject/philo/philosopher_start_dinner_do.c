/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start_dinner_do.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/16 18:35:55 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	eat_with_fork_1(t_thread_param *param, t_fork *first_fork,
				t_fork *second_fork);
static int	eat_with_fork_2(t_thread_param *param, t_fork *first_fork,
				t_fork *second_fork);

int	p_eat(t_thread_param *param)
{
	t_table	*table;
	t_fork	*left_fork;
	t_fork	*right_fork;
	int		id;
	int		starve_count;

	table = param->table;
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	id = table->philo->id;
	starve_count = table->philo->starve_count;
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	left_fork = table->prev->fork;
	right_fork = table->next->fork;
	if (eat_with_fork_1(param, left_fork, right_fork))
		return (-1);
	if (eat_with_fork_2(param, left_fork, right_fork))
		return (-1);
	return (0);
}

static int	eat_with_fork_1(t_thread_param *param,
	t_fork *first_fork, t_fork *second_fork)
{
	pthread_mutex_lock(&(first_fork->fork_mutex));
	first_fork->fork_owner = param->table->philo->id;
	if (my_dead_check(param->table->philo))
	{
		pthread_mutex_unlock(&(first_fork->fork_mutex));
		return (-1);
	}
	print_func(param->info, first_fork, "fork");
	pthread_mutex_lock(&(second_fork->fork_mutex));
	second_fork->fork_owner = param->table->philo->id;
	if (my_dead_check(param->table->philo))
	{
		pthread_mutex_unlock(&(first_fork->fork_mutex));
		pthread_mutex_unlock(&(second_fork->fork_mutex));
		return (-1);
	}
	print_func(param->info, second_fork, "fork");
	if (my_dead_check(param->table->philo))
	{
		pthread_mutex_unlock(&(first_fork->fork_mutex));
		pthread_mutex_unlock(&(second_fork->fork_mutex));
		return (-1);
	}
	return (0);
}

static int	eat_with_fork_2(t_thread_param *param,
	t_fork *first_fork, t_fork *second_fork)
{
	pthread_t	thread;

	pthread_mutex_lock(&param->table->philo->philo_mutex);
	param->table->philo->starve_count ++;
	param->table->philo->state = EATING_STATE;
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	if (my_dead_check(param->table->philo))
	{
		pthread_mutex_unlock(&(first_fork->fork_mutex));
		pthread_mutex_unlock(&(second_fork->fork_mutex));
		return (-1);
	}
	print_func(param->info, param->table->philo, "state");
	pthread_create(&thread, NULL, run_dead_timer_thread_func, (void *)param);
	pthread_detach(thread);
	busy_sleep(param->info->time_to_eat * 1000);
	first_fork->fork_owner = 0;
	pthread_mutex_unlock(&(first_fork->fork_mutex));
	second_fork->fork_owner = 0;
	pthread_mutex_unlock(&(second_fork->fork_mutex));
	return (0);
}

int	p_sleep(t_thread_param *param)
{
	if (my_dead_check(param->table->philo))
		return (-1);
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	param->table->philo->state = SLEEPING_STATE;
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	print_func(param->info, param->table->philo, "state");
	busy_sleep(param->info->time_to_sleep * 1000);
	printf("%d sleep time_check\n", param->table->philo->id);
	print_func(param->info, param->table->philo, "state");
	return (0);
}

int	p_think(t_thread_param *param)
{
	// printf("time check\n");
	// print_func(param->info, param->table->philo, "state");
	if (my_dead_check(param->table->philo))
		return (-1);
	pthread_mutex_lock(&param->table->philo->philo_mutex);
	param->table->philo->state = THINKING_STATE;
	pthread_mutex_unlock(&param->table->philo->philo_mutex);
	print_func(param->info, param->table->philo, "state");
	return (0);
}
