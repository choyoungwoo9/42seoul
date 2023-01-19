/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_set_dinner.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/16 18:21:41 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void		set_table(int philo_count, t_table **leader);
static t_table	*set_philo(int index);
static t_table	*set_fork(void);

int	set_dinner(t_dinner_info *info, int argc, char **argv)
{
	int	i;
	int	num_array[5];

	i = 0;
	while (++i < argc)
	{
		if (!is_integer(*(argv + i), (num_array + i - 1)))
			return (-1);
	}
	info->phil_num = num_array[0];
	info->time_to_die = num_array[1];
	info->time_to_eat = num_array[2];
	info->time_to_sleep = num_array[3];
	if (argc == 5)
		info->phil_must_eat = -1;
	else if (argc == 6)
		info->phil_must_eat = num_array[4];
	set_table(info->phil_num, &(info->leader));
	info->dead_flag = FIRST_STATE;
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->print_mutex, NULL);
	return (1);
}

static void	set_table(int philo_count, t_table **leader)
{
	int		i;
	t_table	*tmp;
	t_table	*prepared_struct;

	i = 0;
	while (++i <= (philo_count * 2))
	{
		if (i % 2)
			prepared_struct = set_philo(i);
		else if (!(i % 2))
			prepared_struct = set_fork();
		if (i == 1)
			*leader = prepared_struct;
		else
		{
			tmp->next = prepared_struct;
			prepared_struct->prev = tmp;
		}
		if (i == (philo_count * 2))
		{
			prepared_struct->next = *leader;
			(*leader)->prev = prepared_struct;
		}
		tmp = prepared_struct;
	}
}

static t_table	*set_philo(int index)
{
	t_table	*ret_value;

	ret_value = malloc(sizeof(t_table));
	ret_value->philo = malloc(sizeof(t_philo));
	ret_value->philo->state = FIRST_STATE;
	ret_value->philo->id = (index + 1) / 2;
	ret_value->philo->starve_count = 1;
	ret_value->philo->dinner_count = 0;
	pthread_mutex_init(&(ret_value->philo->philo_mutex), NULL);
	ret_value->fork = NULL;
	return (ret_value);
}

static t_table	*set_fork(void)
{
	t_table	*ret_value;

	ret_value = malloc(sizeof(t_table));
	ret_value->fork = malloc(sizeof(t_fork));
	ret_value->fork->fork_owner = 0;
	pthread_mutex_init(&(ret_value->fork->fork_mutex), NULL);
	ret_value->philo = NULL;
	return (ret_value);
}
