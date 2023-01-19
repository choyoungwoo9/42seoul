/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:35:11 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/16 18:19:38 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				state;
	int				starve_count;
	int				dinner_count;
	pthread_mutex_t	philo_mutex;
	pthread_t		philo_thread;
}	t_philo;

typedef struct s_fork
{
	int				fork_owner;
	pthread_mutex_t	fork_mutex;
	pthread_t		fork_thread;
}	t_fork;

typedef struct s_table
{
	t_philo			*philo;
	t_fork			*fork;
	struct s_table	*prev;
	struct s_table	*next;
}	t_table;

typedef struct s_dinner_info
{
	t_table			*leader;
	struct timeval	start_time;
	pthread_t		observe_thread;
	pthread_mutex_t	print_mutex;
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				phil_must_eat;
	pthread_mutex_t	dead_mutex;
	int				dead_flag;
}	t_dinner_info;

typedef struct s_thread_param
{
	t_table			*table;
	t_dinner_info	*info;
}	t_thread_param;

# define FIRST_STATE 0
# define THINKING_STATE 1
# define SLEEPING_STATE 2
# define EATING_STATE 3
# define DEAD_STATE -1
# define TRUE 1
# define FALSE 0

int		set_dinner(t_dinner_info *info, int argc, char **argv);
int		p_sleep(t_thread_param *param);
int		p_think(t_thread_param *param);
int		p_eat(t_thread_param *param);
void	start_dinner(t_dinner_info *info);
void	*run_dead_timer_thread_func(void *param);
int		is_integer(char *argv, int *value);
void	observe_dinner(t_dinner_info *info);
int		print_func(t_dinner_info *info, void *data, char *mode);
int		is_anyone_dead(t_dinner_info *info);
int		check_all_philo_eat_must_dinner(t_dinner_info *info);
int		global_dead_check(t_dinner_info *info);
int		my_dead_check(t_philo *philo);
void	print_dead(t_dinner_info *info, t_philo *philo);
void	sleep_strategy(t_thread_param *par);
void busy_sleep(unsigned long long sleep_us);
#endif