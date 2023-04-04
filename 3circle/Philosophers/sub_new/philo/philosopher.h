/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:09:56 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/28 16:38:27 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_flag
{
	int				end_flag;
	int				must_break_count;
	int				must_eat;
	int				philo_num;
	struct timeval	start_time;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	print_mutex;
}	t_flag;

typedef struct s_philo
{
	t_flag			*flag_ref;
	pthread_t		pthread;
	pthread_mutex_t	mutex;
	int				hungry_count;
	int				eat_count;
	int				id;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;	
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_table
{
	t_philo			*philo;
	t_fork			*fork;
	struct s_table	*prev;
	struct s_table	*next;
}	t_table;

typedef struct s_info
{
	t_flag	flag;
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	t_table	*head;
}	t_info;

# define NONE 0
# define D_STATE 1
# define E_STATE 2
# define S_STATE 3
# define T_STATE 4
# define F_STATE 5

void	end_check(t_info *info);
int		is_integer(char *argv, int *value);
void	busy_sleep(unsigned long long sleep_us);
void	thread_init(t_info *info);
int		make_table(t_info *info, int argc, char **argv);
int		print_func(int id, int state, t_philo *philo);
void	*start_dead_timer(void *param);
int		do_routine(t_table *table);
#endif