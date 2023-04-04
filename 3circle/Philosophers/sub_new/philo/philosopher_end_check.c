/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_end_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:42:39 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/27 20:12:14 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*watch_flag(void *param)
{
	t_info	*info;
	int		dead_flag;

	info = (t_info *)param;
	while (1)
	{
		pthread_mutex_lock(&info->flag.flag_mutex);
		dead_flag = info->flag.end_flag;
		pthread_mutex_unlock(&info->flag.flag_mutex);
		if (dead_flag == D_STATE)
		{
			usleep(1000 * info->time_to_die
				+ 1000 * info->time_to_sleep + 1000 * info->time_to_eat);
			break ;
		}
	}
	return ((void *)0);
}

void	end_check(t_info *info)
{
	pthread_t	watch_pthread;

	pthread_create(&watch_pthread, (void *)0, watch_flag, (void *)info);
	pthread_join(watch_pthread, (void *)0);
}
