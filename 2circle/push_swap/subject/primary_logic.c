/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:52:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 17:38:18 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_rotate_count(t_stack *a_head)
{
	t_stack *tmp_stack;
	int ra_rra_count;
	tmp_stack = a_head;

	ra_rra_count = 1;
	while(tmp_stack)
	{
		if(tmp_stack->next)
		{
			if(tmp_stack->number > tmp_stack->next->number)
				break ;
		}
		else
		{
			ra_rra_count = 0;
			break ;
		}
		ra_rra_count ++;
		tmp_stack = tmp_stack->next;
	}
	if(ra_rra_count > find_list_length(a_head) - ra_rra_count)
		ra_rra_count = (find_list_length(a_head) - ra_rra_count) * -1;
	return ra_rra_count;
}

static void	rotate_a(int ra_rra_count, t_stack **a_head, t_stack **a_tail)
{
	while(ra_rra_count)
	{
		if(ra_rra_count > 0)
		{
			operation_ra(a_head, a_tail);
			ra_rra_count --;
		}
		else
		{
			operation_rra(a_head, a_tail);
			ra_rra_count ++;
		}
	}
}

void align_stack(t_stack **a_head, t_stack **a_tail)
{
	t_stack *tmp_stack;
	int ra_rra_count;
	tmp_stack = *a_head;
	if(!tmp_stack)
		return ;
	ra_rra_count = find_rotate_count(tmp_stack);
	rotate_a(ra_rra_count, a_head, a_tail);
	//printf("ra_rra_count : %d\n", ra_rra_count);
}

void	partition(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	t_stack	*tmp_node;
	int		count;
	int		pivot;

	pivot = find_pivot(*a_head);
	tmp_node = *a_head;
	count = find_list_length(*a_head);
	while(--count >= 0 || count >= find_list_length(*b_head))
	{
		if(tmp_node->number < pivot)
			operation_pb(a_head, a_tail, b_head, b_tail);
		else
			operation_ra(a_head, a_tail);
		tmp_node = *a_head;
	}
	while(tmp_node)
	{
		operation_pb(a_head, a_tail, b_head, b_tail);
		tmp_node = *a_head;
	}
}