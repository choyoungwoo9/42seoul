/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sleep_strategy.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:02:36 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/16 18:41:33 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	odd_strategy(t_philo *philo, t_dinner_info *info)
{
	if (philo->id == info->phil_num)
	{
		if (philo->dinner_count == 0)
		{
			busy_sleep(info->time_to_eat * 2000);
		}
	}
	else if (philo->id % 2)
	{
		if (philo->dinner_count == 0)
		{
			busy_sleep(info->time_to_eat * 1000);
		}
	}
	else if (!(philo->id % 2))
	{
	}
}

static void	even_strategy(t_philo *philo, t_dinner_info *info)
{
	if (philo->id % 2)
	{
		if (philo->dinner_count == 0)
		{
			busy_sleep(info->time_to_eat * 950);
		}
	}
	else if (!(philo->id % 2))
	{
	}
}

void	sleep_strategy(t_thread_param *par)
{
	if (par->info->phil_num % 2)
		odd_strategy(par->table->philo, par->info);
	else if (!(par->info->phil_num % 2))
	{
		even_strategy(par->table->philo, par->info);
	}
}
