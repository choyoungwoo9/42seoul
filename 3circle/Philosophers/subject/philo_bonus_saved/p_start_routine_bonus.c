/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_start_routine_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:18:14 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/13 19:10:01 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"

void do_philo_routine(t_philo *philo, t_info info, t_mysem sem)
{
	//print_info(info);
	pthread_t thread;
	pthread_create(&thread, NULL, on_dead_timer, make_param(philo, info, sem));
	while(1)
	{
		//printf("%d first : %d\n", philo->id, philo->starve_count);
		p_think(philo, info, sem.print_sem);
		p_eat(philo, info, sem);
		p_sleep(philo, info, sem.print_sem);
	}
}

void start_dinner(t_mysem sem, t_info info)
{
	int	i;
	int	pid;
	t_philo philo;
	i = 0;
	while(++i <= 10)
	{
		pid = fork();
		if(pid == 0)
		{
			set_philo(i, &philo);
			do_philo_routine(&philo, info, sem);
		}
	}
}

void *make_param(t_philo *philo, t_info info, t_mysem sem)
{
	t_param *ret_param;
	ret_param = malloc(sizeof(t_param));
	ret_param->info = info;
	ret_param->philo = philo;
	ret_param->sem = sem;
	return ((void *)ret_param);
}
