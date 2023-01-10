#include "philosopher.h"

void set_info(t_info *info)
{
	info->phil_num = 10;
	info->time_to_die = 1000;
	info->time_to_eat = 300;
	info->time_to_sleep = 100;
	info->must_eat_num = -1;
	pthread_mutex_init(&info->print_mutex, NULL);
}

t_table *set_philo(int index)
{
	t_table *assigned_table;

	assigned_table = malloc(sizeof(t_table));
	assigned_table->philo = malloc(sizeof(t_philo));
	assigned_table->philo->id = (index + 1)/2;
	assigned_table->philo->starve_count = 1;
	assigned_table->philo->dinner_count = 0;
	assigned_table->philo->state = FIRST_STATE;
	assigned_table->fork = NULL;
	return (assigned_table);
}

t_table *set_fork()
{
	t_table *assigned_table;
	
	assigned_table = malloc(sizeof(t_table));
	assigned_table->fork = malloc(sizeof(t_fork));
	assigned_table->fork->owner = 0;
	pthread_mutex_init(&assigned_table->fork->mu, NULL);
	assigned_table->philo = NULL;
	return (assigned_table);
}

void make_table(t_table **leader_seat, int phil_num)
{
	int i;
	t_table *assigned_table;
	t_table *tmp_table;

	i = 0;
	while(++ i <= phil_num * 2)
	{
		if(i%2)
			assigned_table = set_philo(i);
		else
			assigned_table = set_fork();
		if (i == 1)
			*leader_seat = assigned_table;
		else
		{
			tmp_table->next = assigned_table;
			assigned_table->prev = tmp_table;
		}
		if(i == phil_num * 2)
		{
			assigned_table->next = *leader_seat;
			(*leader_seat)->prev = assigned_table;
		}
		tmp_table = assigned_table;
	}
}
void set_dinner(t_dinner *dinner)
{
	set_info(&dinner->info);
	make_table(&dinner->leader_seat, dinner->info.phil_num);
}
