/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_eat_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:16:30 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/15 19:40:28 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"

void *on_dead_timer(void *param)
{
	t_philo *philo;
	t_info info;
	t_mysem sem;
	philo = ((t_param *)param)->philo;
	info = ((t_param *)param)->info;
	sem = ((t_param *)param)->sem;
	usleep(1000 * info.time_to_die);
	//printf("state :::: %d\n", philo->state);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->starve_count --;
	pthread_mutex_unlock(&philo->philo_mutex);
	printf("%d in time starve : %d\n", philo->id, philo->starve_count);
	if(philo->starve_count <= 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		philo->state = DEAD_STATE;
		pthread_mutex_unlock(&philo->philo_mutex);
		print_state(philo, sem.print_sem, "p");
		printf("i kill you\n");
		kill(0, SIGINT);
		return NULL;
	}
	return NULL;
}

void p_eat(t_philo *philo, t_info info, t_mysem sem)
{
	pthread_t	thread;
	sem_wait(sem.fork_sem);
	sem_wait(sem.fork_sem);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->state = EATING_STATE;
	pthread_mutex_unlock(&philo->philo_mutex);	
	print_state(philo, sem.print_sem, "philo");
	usleep(1000 * info.time_to_eat);
	sem_post(sem.fork_sem);
	sem_post(sem.fork_sem);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->starve_count ++;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_create(&thread, NULL, on_dead_timer, make_param(philo, info, sem));
}
