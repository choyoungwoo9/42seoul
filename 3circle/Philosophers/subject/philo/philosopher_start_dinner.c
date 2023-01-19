/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start_dinner.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/16 18:33:48 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*philo_routine(void *param);
static void	*set_param(t_dinner_info *info, t_table *table);
static void	start_philo_thread(t_dinner_info *info);

void	start_dinner(t_dinner_info *info)
{
	start_philo_thread(info);
}

static void	start_philo_thread(t_dinner_info *info)
{
	int		i;
	t_table	*tmp;

	i = 0;
	tmp = info->leader;
	while (++ i <= info->phil_num)
	{
		if (i == 1)
			gettimeofday(&(info->start_time), NULL);
		pthread_create(&(tmp->philo->philo_thread), NULL, philo_routine,
			set_param(info, tmp));
		pthread_detach(tmp->philo->philo_thread);
		tmp = tmp->next->next;
	}
}

static void	*set_param(t_dinner_info *info,
	t_table *table)
{
	t_thread_param	*param;

	param = malloc(sizeof(t_thread_param));
	param->info = info;
	param->table = table;
	return (param);
}

static void	*philo_routine(void *param)
{
	pthread_t		thread_first;
	t_thread_param	*par;

	par = (t_thread_param *)param;
	pthread_create(&thread_first, NULL, run_dead_timer_thread_func, param);
	pthread_detach(thread_first);
	if (p_think(par) == -1)
		return (&par->table->philo->id);
	while (1)
	{
		sleep_strategy(par);
		if (p_eat(par) == -1)
			return (&par->table->philo->id);
		if (p_sleep(par) == -1)
			return (&par->table->philo->id);
		if (p_think(par) == -1)
			return (&par->table->philo->id);
	}
	return (NULL);
}

void	*run_dead_timer_thread_func(void *param)
{
	t_thread_param	*par;
	int				tmp_count;

	par = (t_thread_param *)param;
	busy_sleep(par->info->time_to_die * 1000);
	pthread_mutex_lock(&par->table->philo->philo_mutex);
	(par->table->philo->dinner_count)++;
	(par->table->philo->starve_count)--;
	tmp_count = par->table->philo->starve_count;
	pthread_mutex_unlock(&par->table->philo->philo_mutex);
	if (tmp_count <= 0)
	{
		pthread_mutex_lock(&par->table->philo->philo_mutex);
		par->table->philo->state = DEAD_STATE;
		pthread_mutex_unlock(&par->table->philo->philo_mutex);
		print_dead(par->info, par->table->philo);
	}
	return (NULL);
}
