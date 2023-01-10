/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_start_dinner_do.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/09 12:01:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philosopher.h"



void	sleep_and_think(t_thread_param *param)
{
	int	id;

	id = param->philo_and_fork->philo->id;
	// if(!is_anyone_dead(param->info) && !check_all_philo_eat_must_dinner(param->info))
	// {
		param->philo_and_fork->philo->state = SLEEPING_STATE;
		print_philo_state(param->info, param->philo_and_fork->philo);
	//}
	// else
	// 	return ;
	usleep(param->info->time_to_sleep * 1000);
	// if(!is_anyone_dead(param->info) && !check_all_philo_eat_must_dinner(param->info))
	// {
		param->philo_and_fork->philo->state = THINKING_STATE;
		print_philo_state(param->info, param->philo_and_fork->philo);
	//}
}

void left_handed_eat(t_thread_param *param)
{
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t thread;

	left_fork = param->philo_and_fork->prev->fork;
	right_fork = param->philo_and_fork->next->fork;
	pthread_mutex_lock(&(left_fork->fork_mutex));
	pthread_mutex_lock(&(right_fork->fork_mutex));
	left_fork->fork_owner = param->philo_and_fork->philo->id;
	right_fork->fork_owner = param->philo_and_fork->philo->id;
	// if(!is_anyone_dead(param->info) && !check_all_philo_eat_must_dinner(param->info))
	// {
		param->philo_and_fork->philo->starve_count ++;
		param->philo_and_fork->philo->state = EATING_STATE;
		print_philo_state(param->info, param->philo_and_fork->philo);
		pthread_create(&thread, NULL, run_dead_timer_thread_func, (void *)param);
	//}
	usleep(param->info->time_to_eat * 1000);
	left_fork->fork_owner = 0;
	right_fork->fork_owner = 0;
	pthread_mutex_unlock(&(left_fork->fork_mutex));
	pthread_mutex_unlock(&(right_fork->fork_mutex));
}

void right_handed_eat(t_thread_param *param)
{
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t thread;

	left_fork = param->philo_and_fork->prev->fork;
	right_fork = param->philo_and_fork->next->fork;
	pthread_mutex_lock(&(right_fork->fork_mutex));
	pthread_mutex_lock(&(left_fork->fork_mutex));
	left_fork->fork_owner = param->philo_and_fork->philo->id;
	right_fork->fork_owner = param->philo_and_fork->philo->id;
	// if(!is_anyone_dead(param->info) && !check_all_philo_eat_must_dinner(param->info))
	// {
		param->philo_and_fork->philo->starve_count ++;
		param->philo_and_fork->philo->state = EATING_STATE;
		print_philo_state(param->info, param->philo_and_fork->philo);
		pthread_create(&thread, NULL, run_dead_timer_thread_func, (void *)param);
	//}
	usleep(param->info->time_to_eat * 1000);
	left_fork->fork_owner = 0;
	right_fork->fork_owner = 0;
	pthread_mutex_unlock(&(left_fork->fork_mutex));
	pthread_mutex_unlock(&(right_fork->fork_mutex));
}

void	eat(t_thread_param *param)
{
	t_philo_and_fork	*philo_and_fork;
	t_fork				*left_fork;
	t_fork				*right_fork;

	philo_and_fork = param->philo_and_fork;
	left_fork = philo_and_fork->prev->fork;
	right_fork = philo_and_fork->next->fork;
	if (philo_and_fork->philo->id%2)
		left_handed_eat(param);
	else
		right_handed_eat(param);
}
