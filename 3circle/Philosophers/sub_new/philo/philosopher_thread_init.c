/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:03 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/28 17:18:48 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*start_routine(void *param)
{
	t_philo		*philo;
	pthread_t	dead_timer_thread;

	philo = ((t_table *)param)->philo;
	pthread_create(&dead_timer_thread, (void *)0, start_dead_timer, param);
	pthread_detach(dead_timer_thread);
	print_func(philo->id, T_STATE, philo);
	if (philo->philo_num % 2 == 0)
	{
		if (philo->id % 2)
			busy_sleep(philo->time_to_eat * 1000);
	}
	else if (philo->philo_num % 2 == 1)
	{
		if (philo->id == philo->philo_num)
			busy_sleep(philo->time_to_eat * 1000 * 2);
		else if (philo->id % 2)
			busy_sleep(philo->time_to_eat * 1000);
	}
	while (1)
	{
		if (!do_routine(param))
			break ;
	}
	return ((void *)0);
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
		pthread_detach(cur->philo->pthread);
		cur = cur->next->next;
	}
}

