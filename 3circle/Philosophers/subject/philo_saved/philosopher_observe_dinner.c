/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_observe_dinner.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/14 09:53:43 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_anyone_dead(t_dinner_info *info)
{
	int					i;
	int					state;
	t_table	*tmp;

	i = 0;
	tmp = info->leader;
	while (++i <= info->phil_num)
	{
		pthread_mutex_lock(&tmp->philo->philo_mutex);
		state = tmp->philo->state;
		pthread_mutex_unlock(&tmp->philo->philo_mutex);
		if (state == DEAD_STATE)
			return (1);
		tmp = tmp->next->next;
	}
	return (0);
}

int	check_all_philo_eat_must_dinner(t_dinner_info *info)
{
	int					i;
	int					tmp_dinner_count;
	t_table	*tmp;

	tmp = info->leader;
	if (info->phil_must_eat == -1)
		return (0);
	i = 0;
	while (++i <= info->phil_num)
	{
		pthread_mutex_lock(&tmp->philo->philo_mutex);
		tmp_dinner_count = tmp->philo->dinner_count;
		pthread_mutex_unlock(&tmp->philo->philo_mutex);
		if (tmp_dinner_count < info->phil_must_eat)
			return (0);
		tmp = tmp->next->next;
	}
	return (1);
}

void	*observe_thread(void *param)
{
	t_dinner_info	*info;

	info = (t_dinner_info *)param;
	while (1)
	{
		if (is_anyone_dead(info))
			break ;
		if (check_all_philo_eat_must_dinner(info))
			break ;
	}
	return (NULL);
}

void	observe_dinner(t_dinner_info	*info)
{
	pthread_create(&info->observe_thread, NULL, observe_thread, info);
	pthread_join(info->observe_thread, NULL);
}