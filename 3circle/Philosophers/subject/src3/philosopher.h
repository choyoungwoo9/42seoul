/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:35:11 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/09 10:48:50 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int id;
	int state;
	int starve_count;
	int dinner_count;
	
	pthread_t philo_thread;
}	t_philo;

typedef struct s_fork
{
	int fork_owner;
	pthread_mutex_t fork_mutex;
	pthread_t fork_thread;
}	t_fork;

typedef struct s_philo_and_fork
{
	int type;
	t_philo *philo;
	t_fork *fork;
	struct s_philo_and_fork *prev;
	struct s_philo_and_fork *next;
}	t_philo_and_fork;


typedef struct s_dinner_info
{
	t_philo_and_fork *leader;
	struct timeval start_time;
	pthread_mutex_t print_mutex;
	int phil_num;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int phil_must_eat;
}	t_dinner_info;

typedef struct s_thread_param
{
	t_philo_and_fork *philo_and_fork;
	t_dinner_info *info;
}	t_thread_param;

#define FIRST_STATE 0
#define THINKING_STATE 1
#define SLEEPING_STATE 2
#define EATING_STATE 3
#define DEAD_STATE -1
#define TYPE_PHILO 1
#define TYPE_FORK 0

int	set_dinner(t_dinner_info *info, int argc, char **argv);
void	sleep_and_think(t_thread_param *param);
void	eat(t_thread_param *param);
void start_dinner(t_dinner_info *info);
void	*run_dead_timer_thread_func(void *param);
int	is_integer(char *argv, int *value);
void observe_dinner(t_dinner_info *info);
void print_philo_state(t_dinner_info *info, t_philo *philo);
void	ft_putnbr(unsigned long long n);
t_philo_and_fork *is_anyone_dead(t_dinner_info *info);
int check_all_philo_eat_must_dinner(t_dinner_info *info);
#endif