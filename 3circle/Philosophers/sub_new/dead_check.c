/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:42:39 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/25 19:34:16 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void *watch_flag(void *param)
{
	t_info *info = (t_info *)param;
	while(1)
	{
		pthread_mutex_lock(&info->flag.dead_flag_mutex);
		if(info->flag.dead_flag == D_STATE)
		{
			pthread_mutex_unlock(&info->flag.dead_flag_mutex);
			break;
		}
		pthread_mutex_unlock(&info->flag.dead_flag_mutex);
	}
	return NULL;
}

void dead_check(t_info *info)
{
	pthread_t watch_pthread;
	pthread_create(&watch_pthread, NULL, watch_flag, (void *)info);
	pthread_join(watch_pthread, NULL);
}