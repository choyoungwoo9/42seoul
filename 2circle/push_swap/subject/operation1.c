/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:22 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/14 17:07:13 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	operation_sa(t_stack *stack_a)
{
	int tmp;
	if(!(stack_a) || !(stack_a->next))
		return ;
	tmp = stack_a->number;
	stack_a->number = stack_a->next->number;
	stack_a->next->number = tmp;
}

void	operation_sb(t_stack *stack_b)
{
	int tmp;
	if(!stack_b || !(stack_b->next))
		return ;
	tmp = stack_b->number;
	stack_b->number = stack_b->next->number;
	stack_b->next->number = tmp;
}

void	operation_ss(t_stack *stack_a, t_stack *stack_b)
{
	operation_sa(stack_a);
	operation_sa(stack_b);
}

void	operation_pa(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	int tmp_num;
	
	if (!(*b_head) || !(*b_tail))
		return ;
	tmp_num = (*b_head)->number;
	pop_top(b_head, b_tail);
	push_top(a_head, a_tail, tmp_num);
}

void	operation_pb(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	int tmp_num;
	
	if (!(*a_head) || !(*a_tail))
		return ;
	tmp_num = (*a_head)->number;
	pop_top(a_head, a_tail);
	push_top(b_head, b_tail, tmp_num);
}