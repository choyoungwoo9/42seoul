/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:22 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 17:03:28 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_operation(t_stack *stack)
{
	int tmp;
	if(!(stack) || !(stack->next))
		return ;
	tmp = stack->number;
	stack->number = stack->next->number;
	stack->next->number = tmp;	
}

void	operation_sa(t_stack *stack_a)
{
	swap_operation(stack_a);
	printf("sa\n");
}

void	operation_sb(t_stack *stack_b)
{
	swap_operation(stack_b);
	printf("sb\n");
}

void	operation_ss(t_stack *stack_a, t_stack *stack_b)
{
	swap_operation(stack_a);
	swap_operation(stack_b);
	printf("ss\n");
}

static void	push_operation(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	int tmp_num;
	
	if (!(*b_head) || !(*b_tail))
		return ;
	tmp_num = (*b_head)->number;
	pop_top(b_head, b_tail);
	push_top(a_head, a_tail, tmp_num);
}

void	operation_pa(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	push_operation(a_head, a_tail, b_head, b_tail);
	printf("pa\n");
}

void	operation_pb(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	push_operation(b_head, b_tail, a_head, a_tail);
	printf("pb\n");
}