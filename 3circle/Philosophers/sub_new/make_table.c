#include "main.h"
#include "util.c"

void make_philo(t_info *info, t_table *table, int id)
{
	table->category = PHILO;
	t_philo *philo= malloc(sizeof(t_philo));
	philo->flag_ref = &info->flag;
	philo->philo_num = info->philo_num;
	philo->time_to_sleep = info->time_to_sleep;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_die = info->time_to_die;
	philo->must_eat = info->must_eat;
	philo->hungry_count = 0;
	philo->eat_count = 0;
	table->philo = philo;
	table->fork = NULL;
	philo->id = id;
}

void make_fork(t_table *table)
{
	table->category = FORK;
	t_fork *fork = malloc(sizeof(t_fork));
	table->fork = fork;
	table->philo = NULL;
	pthread_mutex_init(&table->fork->mutex, NULL);
}

int make_table(t_info *info, int argc, char **argv)
{
	int i;
	int num_array[5];
	i = 0;
	while(++i < argc)
	{
		if(!is_integer(*(argv+i), (num_array+i-1)))
			return -1;
	}
	info->philo_num = num_array[0];
	info->time_to_die = num_array[1];
	info->time_to_eat = num_array[2];
	info->time_to_sleep = num_array[3];
	info->must_eat = -1;
	if(argc == 6)
		info->must_eat = num_array[4];

	info->flag.dead_flag = NONE;
	info->flag.philo_num = info->philo_num;
	info->flag.must_eat = info->must_eat;
	info->flag.must_break_count = 0;
	pthread_mutex_init(&info->flag.dead_flag_mutex, NULL);
	pthread_mutex_init(&info->flag.print_mutex, NULL);
	t_table *before_table = NULL;
	for(int i = 1; i <= info->philo_num * 2; i ++)
	{
		t_table *cur_table = malloc(sizeof(t_table));
		if(i % 2 == 1)
			make_philo(info, cur_table, i/2+1);
		else if(i % 2 == 0)
			make_fork(cur_table);
		if(before_table)
		{
			before_table->next = cur_table;
			cur_table->prev = before_table;
		}
		else
		{
			before_table = cur_table;
			info->head = before_table;
		}
		if(i == info->philo_num * 2)
		{
			cur_table->next = info->head;
			info->head->prev = cur_table;
		}
		before_table = cur_table;
	}
	return 1;
}

