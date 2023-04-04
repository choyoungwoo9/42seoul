/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_do.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:02:07 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/28 17:05:02 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	p_eat(t_table *table)
{
	pthread_t	dead_timer_thread;

	pthread_mutex_lock(&table->next->fork->mutex);
	pthread_mutex_lock(&table->prev->fork->mutex);
	if (!print_func(table->philo->id, F_STATE, table->philo))
	{
		pthread_mutex_unlock(&table->next->fork->mutex);
		pthread_mutex_unlock(&table->prev->fork->mutex);
		return (0);
	}
	pthread_create(&dead_timer_thread, (void *)0, start_dead_timer, table);
	pthread_detach(dead_timer_thread);
	table->philo->eat_count ++;
	if (!print_func(table->philo->id, E_STATE, table->philo))
	{
		pthread_mutex_unlock(&table->next->fork->mutex);
		pthread_mutex_unlock(&table->prev->fork->mutex);
		return (0);
	}
	busy_sleep(table->philo->time_to_eat * 1000);
	pthread_mutex_unlock(&table->next->fork->mutex);
	pthread_mutex_unlock(&table->prev->fork->mutex);
	return (1);
}

int	p_sleep(t_table *table)
{
	if (!print_func(table->philo->id, S_STATE, table->philo))
	{
		return (0);
	}
	busy_sleep(table->philo->time_to_sleep * 1000);
	print_func(table->philo->id, S_STATE, table->philo);
	return (1);
}

int	p_think(t_table *table)
{
	if (!print_func(table->philo->id, T_STATE, table->philo))
		return (0);
	if (table->philo->philo_num % 2 == 1)
		busy_sleep(table->philo->time_to_eat * 1000);
	return (1);
}

int	do_routine(t_table *table)
{
	usleep(100);
	if (!p_eat(table))
		return (0);
	if (!p_sleep(table))
		return (0);
	if (!p_think(table))
		return (0);
	return (1);
}
