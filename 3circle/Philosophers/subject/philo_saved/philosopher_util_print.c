/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:39:41 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/14 15:21:16 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_fork_state(t_dinner_info *info, t_fork *fork)
{
	printf("%d has taken a fork\n", fork->fork_owner);
	pthread_mutex_unlock(&info->print_mutex);
	return ;
}

static void	print_state(t_dinner_info *info, t_philo *philo)
{
	if (philo->state == EATING_STATE)
		printf("%d is eating\n", philo->id);
	if (philo->state == SLEEPING_STATE)
		printf("%d is sleeping\n", philo->id);
	if (philo->state == THINKING_STATE)
		printf("%d is thinking\n", philo->id);
	if (philo->state == DEAD_STATE)
	{
		printf("%d died\n", philo->id);
		return ;
	}
	pthread_mutex_unlock(&info->print_mutex);
}

void	print_func(t_dinner_info *info, void *data, char *mode)
{
	struct timeval		time;
	unsigned long long	current_ms;

	pthread_mutex_lock(&info->print_mutex);
	gettimeofday(&time, NULL);
	current_ms = (time.tv_sec - info->start_time.tv_sec) * 1000
		+ (time.tv_usec - info->start_time.tv_usec) / 1000;
	printf("%llums ", current_ms);
	if (*mode == 's')
		print_state(info, (t_philo *)data);
	else if (*mode == 'f')
		print_fork_state(info, (t_fork *)data);
}
