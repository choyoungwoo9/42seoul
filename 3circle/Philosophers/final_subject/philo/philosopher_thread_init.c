/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:03 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/02 08:31:41 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	sleep_strategy(t_philo *philo)
{
	if (philo->philo_num % 2 == 0)
	{
		if (philo->id % 2)
		{
			if (!busy_sleep(philo->time_to_eat * 1000, philo))
				return (0);
		}
	}
	else if (philo->philo_num % 2 == 1)
	{
		if (philo->id == philo->philo_num)
		{
			if (!busy_sleep(philo->time_to_eat * 1000 * 2, philo))
				return (0);
		}
		else if (philo->id % 2)
		{
			if (philo->id % 2)
			{
				if (!busy_sleep(philo->time_to_eat * 1000, philo))
					return (0);
			}
		}
	}
	return (1);
}

static void	*check_joinable(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->assert_flag == D_STATE)
		{
			pthread_mutex_unlock(&philo->mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return ((void *)0);
}

void	*start_routine(void *param)
{
	t_philo		*philo;

	philo = ((t_table *)param)->philo;
	gettimeofday(&philo->eat_time, (void *)0);
	if (!print_func(philo->id, T_STATE, philo))
	{
		check_joinable(philo);
		return (check_joinable(philo));
	}
	if (!sleep_strategy(philo))
		return (check_joinable(philo));
	if (philo->philo_num == 1)
	{
		if (!sleep_strategy(philo))
			return (check_joinable(philo));
	}
	while (1)
	{
		if (!do_routine(param))
			break ;
	}
	return (check_joinable(philo));
}

void	thread_init(t_info *info)
{
	t_table	*cur;
	int		i;

	cur = info->head;
	i = 0;
	while (++ i <= info->philo_num)
	{
		pthread_create(
			&cur->philo->pthread, (void *)0, start_routine, (void *)cur);
		cur = cur->next->next;
	}
}
