/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:16:05 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/10 17:06:08 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "p_set_dinner.c"

void *philo_routine(void *param)
{
	printf("routine_start");
	t_info *info = ((t_param *)param)->info;
	t_table *table = ((t_param *)param)->table;
	while(1)
	{
		//think ->no wait 
		//eat -> set timer
		//sleep -> wait
	}
	return NULL;
}

t_param *set_param(t_table *table, t_dinner *dinner)
{
	
	table->philo->param = (void *)malloc(sizeof(t_param));
	t_param *param;
	param = (t_param *)table->philo->param;
	param->info = &dinner->info;
	param->table = table;
	return param;
}

void start_phil_thread(t_dinner *dinner)
{
	int i;
	t_info info;
	t_table *table;
	t_param *param;

	info = dinner->info;
	table = dinner->leader_seat;
	i = 0;
	printf("numnum  %d\n", dinner->info.phil_num);
	while (++ i <= info.phil_num)
	{
		param = set_param(table, dinner);
		pthread_create(&table->philo->th, NULL, philo_routine, (void *)&param);
		//table = table->next->next;
	}
	//printf("numnum  %d\n", dinner->info.phil_num);
}

void start_dinner(t_dinner *dinner)
{
	start_phil_thread(dinner);
}


int main()
{
	t_dinner dinner;
	set_dinner(&dinner);
	start_dinner(&dinner);
	sleep(1);
	//observe_dinner();
}
