/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_primary_util.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:24:03 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/02 08:23:18 by youngwch         ###   ########.fr       */
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
	pthread_mutex_lock(&flag->flag_mutex);
	if (flag->end_flag == D_STATE)
	{
		pthread_mutex_unlock(&flag->flag_mutex);
		return (0);
	}
	if (state == E_STATE && philo->eat_count == philo->must_eat)
		flag->must_break_count ++;
	if (flag->must_break_count == philo->philo_num)
		flag->end_flag = D_STATE;
	if (state == D_STATE)
		flag->end_flag = D_STATE;
	print_logic(id, state, philo);
	pthread_mutex_unlock(&flag->flag_mutex);
	return (1);
}
