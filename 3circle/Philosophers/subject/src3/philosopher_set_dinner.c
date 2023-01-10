/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_set_dinner.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/10 17:10:57 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo_and_fork *set_philo(int index)
{
	t_philo_and_fork	*ret_value;

	ret_value = malloc(sizeof(t_philo_and_fork));
	ret_value->type = TYPE_PHILO;
	ret_value->philo = malloc(sizeof(t_philo));
	ret_value->philo->state = FIRST_STATE;
	ret_value->philo->id = (index + 1)/2;
	ret_value->philo->starve_count = 1;
	ret_value->philo->dinner_count = 0;
	ret_value->fork = NULL;
	return (ret_value);
}

static t_philo_and_fork	*set_fork()
{
	t_philo_and_fork *ret_value;

	ret_value = malloc(sizeof(t_philo_and_fork));
	ret_value->type = TYPE_FORK;
	ret_value->fork = malloc(sizeof(t_fork));
	ret_value->fork->fork_owner = 0;
	pthread_mutex_init(&(ret_value->fork->fork_mutex), NULL);
	ret_value->philo = NULL;
	return (ret_value);
}

static void	set_philo_fork_seat(int philo_count, t_philo_and_fork **leader)
{
	int i;
	t_philo_and_fork *tmp;
	t_philo_and_fork *prepared_struct;

	i = 0;
	while (++i <= (philo_count * 2))
	{
		if (i%2)
			prepared_struct = set_philo(i);
		else if (!(i%2))
			prepared_struct = set_fork();
		if (i == 1)
			*leader = prepared_struct;
		else
		{
			tmp->next = prepared_struct;
			prepared_struct->prev = tmp;
		}
		if(i == (philo_count * 2))
		{
			prepared_struct->next = *leader;
			(*leader)->prev = prepared_struct;
		}
		tmp = prepared_struct;
	}
}

int	set_dinner(t_dinner_info *info, int argc, char **argv)
{
	int i;
	int num_array[5];

	i = 0;
	while(++i < argc)
	{
		if(!is_integer(*(argv + i), (num_array + i - 1)))
			return -1;
	}

	info->phil_num = num_array[0];//*(argv + 1);
	info->time_to_die = num_array[1];//*(argv + 2); //먹지않으면 죽는 시간
	info->time_to_eat = num_array[2];//*(argv + 3); //먹는 시간으로 포크를 쥐고있음
	info->time_to_sleep = num_array[3];//*(argv + 4); //자는 시간
	if(argc == 5)
		info->phil_must_eat = -1;
	else if(argc == 6)
		info->phil_must_eat = num_array[4];
	set_philo_fork_seat(info->phil_num, &(info->leader));
	return (0);
}
