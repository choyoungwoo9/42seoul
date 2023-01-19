/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print_state_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:02:30 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/14 09:27:51 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"

static char *make_comment_by_state(int state)
{
	if(state == THINKING_STATE)
		return ("THINK");
	if(state == SLEEPING_STATE)
		return ("SLEEP");
	if(state == EATING_STATE)
		return ("EAT");
	if(state == DEAD_STATE)
		return ("DYE");
	else
		return ("ERROR");
}

static void print_philo_state(t_philo *philo, sem_t *print_sem)
{
	sem_wait(print_sem);
	printf("%d %s\n", philo->id, make_comment_by_state(philo->state));
	pthread_mutex_lock(&philo->philo_mutex);
	int state = philo->state;
	pthread_mutex_unlock(&philo->philo_mutex);
	if(state == DEAD_STATE)
		return ;
	sem_post(print_sem);
}
void	print_state(t_philo *philo, sem_t *print_sem, const char *mode)
{
	if(*mode == 'p')
	{
		print_philo_state(philo, print_sem);
	}
	// else if(*mode == 'f')
	// {
	// 	print_fork_state();
	// }
}