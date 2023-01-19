/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_think_sleep_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:17:18 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/13 19:19:44 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"

void p_think(t_philo *philo, t_info info, sem_t *print_sem)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->state = THINKING_STATE;
	print_state(philo, print_sem, "philo");
	pthread_mutex_unlock(&philo->philo_mutex);
	//printf("thinnk starve : %d\n", philo->starve_count);
}

void	p_sleep(t_philo *philo, t_info info, sem_t *print_sem)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->state = SLEEPING_STATE;
	print_state(philo, print_sem, "philo");
	pthread_mutex_unlock(&philo->philo_mutex);
	usleep(1000 * info.time_to_sleep);
	printf("sleep starve : %d\n", philo->starve_count);
}