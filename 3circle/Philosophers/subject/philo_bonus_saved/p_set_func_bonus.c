/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_set_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:13:09 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/13 19:17:20 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"

void set_philo(int id, t_philo *philo)
{
	philo->id = id;
	philo->state = FIRST_STATE;
	philo->starve_count = 1;
	philo->dinner_count = 0;
	pthread_mutex_init(&philo->philo_mutex, NULL);
}

void set_sem(t_mysem *sem)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem->fork_sem = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, 10);
	sem->print_sem = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
}

void set_info(t_info *info)
{
	info->phil_num = 10;
	info->time_to_die = 1000;
	info->time_to_eat = 500;
	info->time_to_sleep = 501;
	info->phil_must_eat = -1;
	pthread_mutex_init(&info->info_mutex, NULL);
}
