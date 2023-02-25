/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:50:03 by youngwch          #+#    #+#             */
/*   Updated: 2023/02/25 19:41:09 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int print_func(int id, int state, t_philo *philo)
{
	t_flag *flag = philo->flag_ref;
	pthread_mutex_lock(&flag->dead_flag_mutex);
	if(flag->dead_flag == D_STATE)
	{
		pthread_mutex_unlock(&flag->dead_flag_mutex);
		return 0;
	}
	if(state == E_STATE && philo->eat_count == flag->must_eat)
		flag->must_break_count++;
	if(flag->must_break_count == flag->philo_num)
		flag->dead_flag = D_STATE;
	pthread_mutex_lock(&flag->print_mutex);
	if(state == D_STATE)
		flag->dead_flag = D_STATE;
	printf("?? ms ");
	if(state == E_STATE)
		printf("%d is eating\n", id);
	else if(state == S_STATE)
		printf("%d is sleeping\n", id);
	else if(state == T_STATE)
		printf("%d is thinking\n", id);
	else if(state == F_STATE)
		printf("%d has taken a fork\n", id);
	else if(state == D_STATE)
		printf("%d is died\n", id);
	pthread_mutex_unlock(&flag->print_mutex);
	pthread_mutex_unlock(&flag->dead_flag_mutex);
	return 1;
}

void *start_dead_timer(void *param)
{
	t_table *table = (t_table *)param;
	t_philo *philo = table->philo;
	philo->hungry_count ++;
	usleep(1000 * philo->time_to_die);
	philo->hungry_count --;
	if(philo->hungry_count == 0)
	{
		print_func(philo->id, D_STATE, philo);
	}
	return NULL;
}

int p_eat(t_table *table)
{
	int ret_flag;
	ret_flag = 1;
	pthread_t dead_timer_thread;
	pthread_mutex_lock(&table->next->fork->mutex);
	pthread_mutex_lock(&table->prev->fork->mutex);
	pthread_create(&dead_timer_thread, NULL, start_dead_timer, table);
	pthread_detach(dead_timer_thread);
	table->philo->eat_count ++;
	if(!print_func(table->philo->id, E_STATE, table->philo))
	{
		ret_flag = 0;
	}
	usleep(table->philo->time_to_eat);
	pthread_mutex_unlock(&table->next->fork->mutex);
	pthread_mutex_unlock(&table->prev->fork->mutex);
	return ret_flag;
}

int p_sleep(t_table *table)
{
	if(!print_func(table->philo->id, S_STATE, table->philo))
		return 0;
	usleep(table->philo->time_to_sleep * 1000);
	return 1;
}

int p_think(t_table *table)
{
	if(!print_func(table->philo->id, T_STATE, table->philo))
		return 0;
	return 1;
}

int do_routine(t_table *table)
{
	if(!p_eat(table))
		return 0;
	if(!p_sleep(table))
		return 0;
	if(!p_think(table))
		return 0;
	return 1;
}

void *start_routine(void *param)
{
	t_table *table = (t_table *)param;
	t_philo *philo = table->philo;
	pthread_t dead_timer_thread;
	pthread_create(&dead_timer_thread, NULL, start_dead_timer, param);
	pthread_detach(dead_timer_thread);
	print_func(philo->id, T_STATE, philo);
	if(philo->philo_num % 2 == 0 && philo->id % 2)
	{
		usleep(philo->time_to_eat * 1000);
	}
	else
	{
		if(philo->id == philo->philo_num)
		{
			usleep(philo->time_to_eat * 1000 * 2);
		}
		else if(philo->id % 2)
			usleep(philo->time_to_eat * 1000);
	}
	while(1)
	{
		if(!do_routine(param))
			break;
	}
	return NULL;
}

//시작하고 unlock시킬생각(특정인풋에서 바로 끝나서 생기는 문제 예방)
void thread_init(t_info *info)
{
	t_table *cur = info->head;
	for(int i = 0; i < info->philo_num; i ++)
	{
		//printf("i : %d\n", i);
		
		pthread_create(&cur->philo->pthread, NULL, start_routine, (void *)cur);
		pthread_detach(cur->philo->pthread);
		cur = cur->next->next;
	}
}