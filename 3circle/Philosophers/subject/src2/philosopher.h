#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int id;
	int state;
	int starve_count;
	int dinner_count;
	void *param;
	pthread_t th;
	pthread_mutex_t mu;
}	t_philo;

typedef struct s_fork
{
	int owner;
	pthread_t th;
	pthread_mutex_t mu;
}	t_fork;

typedef struct s_table
{
	t_philo *philo;
	t_fork *fork;
	struct s_table *next;
	struct s_table *prev;
}	t_table;

typedef struct s_info
{
	int phil_num;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_num;
	int dead_flag;
	pthread_mutex_t print_mutex;
}	t_info;
typedef struct s_dinner
{
	t_info info;
	t_table *leader_seat;
}	t_dinner;

typedef struct s_param
{
	t_info *info;
	t_table *table;
}	t_param;

#define FIRST_STATE 0
#define THINKING_STATE 1
#define SLEEPING_STATE 2
#define EATING_STATE 3
#define DEAD_STATE -1
#endif