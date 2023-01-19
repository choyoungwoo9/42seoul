/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bonus.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:22:48 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/15 19:24:58 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_BONUS_H
# define P_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct s_mysem
{
	sem_t *fork_sem;
	sem_t *print_sem;
}	t_mysem;

typedef struct s_philo
{
	pthread_mutex_t philo_mutex;
	int id;
	int state;
	int starve_count;
	int dinner_count;
}	t_philo;

typedef struct s_info
{
	struct timeval	start_time;
	pthread_mutex_t info_mutex;
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				phil_must_eat;
}	t_info;

typedef struct s_param
{
	t_philo *philo;
	t_mysem sem;
	t_info info;
}	t_param;

void set_sem(t_mysem *sem);
void set_info(t_info *info);
void set_philo(int id, t_philo *philo);
void	print_state(t_philo *philo, sem_t *print_sem, const char *mode);
void	p_think(t_philo *philo, t_info info, sem_t *print_sem);
void	*make_param(t_philo *philo, t_info info, t_mysem sem);
void	*on_dead_timer(void *param);
void	p_eat(t_philo *philo, t_info info, t_mysem sem);
void	p_sleep(t_philo *philo, t_info info, sem_t *print_sem);
void	do_philo_routine(t_philo *philo, t_info info, t_mysem sem);
void	start_dinner(t_mysem sem, t_info info);
void	print_info(t_info info);

# define FIRST_STATE 0
# define THINKING_STATE 1
# define SLEEPING_STATE 2
# define EATING_STATE 3
# define DEAD_STATE -1

#endif