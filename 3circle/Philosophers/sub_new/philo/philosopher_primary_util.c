/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_primary_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:24:03 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/28 17:05:05 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_logic(int id, int state, t_philo *philo)
{
	struct timeval	time;
	int				current_ms;

	gettimeofday(&time, (void *)0);
	current_ms = (time.tv_sec - philo->flag_ref->start_time.tv_sec) * 1000
		+ (time.tv_usec - philo->flag_ref->start_time.tv_usec) / 1000;
	printf("%dms ", current_ms);
	if (state == E_STATE)
		printf("%d is eating\n", id);
	else if (state == S_STATE)
		printf("%d is sleeping\n", id);
	else if (state == T_STATE)
		printf("%d is thinking\n", id);
	else if (state == F_STATE)
		printf("%d has taken a fork\n", id);
	else if (state == D_STATE)
		printf("%d is died\n", id);
}

int	print_func(int id, int state, t_philo *philo)
{
	t_flag	*flag;

	flag = philo->flag_ref;
	pthread_mutex_lock(&flag->print_mutex);
	if (flag->end_flag == D_STATE)
	{
		pthread_mutex_unlock(&flag->flag_mutex);
		return (0);
	}
	if (state == E_STATE && philo->eat_count == flag->must_eat)
		flag->must_break_count ++;
	if (flag->must_break_count == flag->philo_num)
		flag->end_flag = D_STATE;
	if (state == D_STATE)
		flag->end_flag = D_STATE;
	print_logic(id, state, philo);
	pthread_mutex_unlock(&flag->print_mutex);
	return (1);
}

void	*start_dead_timer(void *param)
{
	int		time_to_die;
	int		id;
	int		hungry_count;
	t_table	*table;
	t_philo	*philo;

	pthread_mutex_lock(&((t_table *)param)->philo->mutex);
	time_to_die = ((t_table *)param)->philo->time_to_die;
	id = ((t_table *)param)->philo->id;
	table = (t_table *)param;
	philo = table->philo;
	philo->hungry_count ++;
	pthread_mutex_unlock(&((t_table *)param)->philo->mutex);
	busy_sleep(1000 * time_to_die);
	pthread_mutex_lock(&((t_table *)param)->philo->mutex);
	philo->hungry_count --;
	hungry_count = philo->hungry_count;
	pthread_mutex_unlock(&((t_table *)param)->philo->mutex);
	if (hungry_count == 0)
		print_func(id, D_STATE, philo);
	return ((void *)0);
}
