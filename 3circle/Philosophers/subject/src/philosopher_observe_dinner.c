/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_observe_dinner.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/09 12:00:54 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void detach_all(t_dinner_info *info)
{
	int i = 0;
	t_philo_and_fork *tmp;

	tmp = info->leader;
	while(++i <= info->phil_num)
	{
		pthread_detach(tmp->philo->philo_thread);
		tmp = tmp->next->next;
	}
}

t_philo_and_fork *is_anyone_dead(t_dinner_info *info)
{
	int i;
	i = 0;
	t_philo_and_fork *tmp = info->leader;
	while(++i <= 10)
	{
		//printf("state : %d\n", tmp->philo->state);
		if(tmp->philo->state == DEAD_STATE)
		{
			return tmp;
		}
		tmp = tmp->next->next;
	}
	return NULL;
}

int check_all_philo_eat_must_dinner(t_dinner_info *info)
{
	t_philo_and_fork *tmp = info->leader;
	int	i;
	if(info->phil_must_eat == -1)
		return (0);
	i = 0;
	while(++i <= info->phil_num)
	{
		if(tmp->philo->dinner_count < info->phil_must_eat)
			return (0);
		tmp = tmp->next->next;
	}
	return 1;
}

void observe_dinner(t_dinner_info *info)
{
	t_philo_and_fork *tmp;
	while(1)
	{
		tmp = is_anyone_dead(info);
		if(tmp)
		{
			//detach_all(info);
			//write(1, "!!!!!!!here\n", 12);
			//print_philo_state(info, tmp->philo);
			break;
		}
		if(check_all_philo_eat_must_dinner(info))
		{
			//detach_all(info);
			write(1, "all_eat\n", 7);
			break;
		}
		
	}
}
