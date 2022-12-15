/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:47:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 17:50:54 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

static int find_ra_count(t_stack *tmp_stack, int number)
{
	int count = 1;
	while(tmp_stack)
	{
		if(tmp_stack->next)
		{
			if(tmp_stack->number < tmp_stack->next->number) //정상적인 상황
			{
				if(tmp_stack->number < number && tmp_stack->next->number > number)
					break;
			}
			else
			{
				if(tmp_stack->number < number || tmp_stack->next->number > number)
					break;
			}
		}
		if(!(tmp_stack->next))
		{
			count = 0;
			break ;
		}
		count ++;
		tmp_stack = tmp_stack->next;
	}
	return count;
}

int count_ra(t_stack *a_head, int number)
{
	int count;
	t_stack *tmp_stack;
	
	tmp_stack = a_head;
	if(!tmp_stack || !(tmp_stack->next))
		return 0;
	count = find_ra_count(tmp_stack, number);
	if(find_list_length(a_head) - count < count)
		count = (find_list_length(a_head) - count) * -1;
	return count;
}

int	count_rb(t_stack *b_head, int number)
{
	int	count;
	t_stack	*tmp_node;

	count = 0;
	tmp_node = b_head;
	while(tmp_node)
	{
		if(tmp_node->number == number)
			break ;
		count ++;
		tmp_node = tmp_node->next;
	}
	if(find_list_length(b_head) - count < count)
		count = (find_list_length(b_head) - count) * -1;
	return count;
}
