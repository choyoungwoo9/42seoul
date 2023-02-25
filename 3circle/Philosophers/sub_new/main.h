# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_flag
{
	int dead_flag;
	int must_break_count;
	int must_eat;
	int philo_num;
	pthread_mutex_t dead_flag_mutex;
	pthread_mutex_t print_mutex;
}	t_flag;

typedef struct s_philo
{
	t_flag *flag_ref;
	pthread_t pthread;
	int hungry_count;
	int eat_count;
	int id;
	int philo_num;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;	
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_table
{
	int category;
	t_philo *philo;
	t_fork *fork;
	struct s_table *prev;
	struct s_table *next;
}	t_table;

typedef struct s_info
{
	t_flag flag;
	int philo_num;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	t_table *head;
}	t_info;

#define PHILO 1
#define FORK 2
#define NONE 0
#define D_STATE 1
#define E_STATE 2
#define S_STATE 3
#define T_STATE 4
#define F_STATE 5

#endif