/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:39:41 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/27 16:42:56 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_fork_state(t_dinner_info *info, t_fork *fork,
	unsigned long long current_ms)
{
	(void)info;
	printf("%llums %d has taken a fork\n", current_ms, fork->fork_owner);
	pthread_mutex_unlock(&info->print_mutex);
	return ;
}

static void	print_state(t_dinner_info *info, t_philo *philo,
	unsigned long long current_ms)
{
	int	state;
	(void)info;
	pthread_mutex_lock(&philo->philo_mutex);
	state = philo->state;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (state == EATING_STATE)
		printf("%llums %d is eating\n", current_ms, philo->id);
	if (state == SLEEPING_STATE)
		printf("%llums %d is sleeping\n", current_ms, philo->id);
	if (state == THINKING_STATE)
		printf("%llums %d is thinking\n", current_ms, philo->id);
	pthread_mutex_unlock(&info->print_mutex);
}

int	print_func(t_dinner_info *info, void *data, char *mode)
{
	struct timeval		time;
	unsigned long long	current_ms;

	pthread_mutex_lock(&info->print_mutex);
	gettimeofday(&time, NULL);
	current_ms = ((unsigned long long)(time.tv_sec - info->start_time.tv_sec) * (unsigned long long)1000000 + (unsigned long long)(time.tv_usec - info->start_time.tv_usec)) / 1000;
	if (*mode == 's')
		print_state(info, (t_philo *)data, current_ms);
	else if (*mode == 'f')
		print_fork_state(info, (t_fork *)data, current_ms);
	return (0);
}

void	print_dead(t_dinner_info *info, t_philo *philo)
{
	struct timeval	time;
	int				current_ms;

	pthread_mutex_lock(&info->print_mutex);
	gettimeofday(&time, NULL);
	current_ms = (time.tv_sec - info->start_time.tv_sec) * 1000
		+ (time.tv_usec - info->start_time.tv_usec) / 1000;
	printf("%dms %d died\n", current_ms, philo->id);
}
