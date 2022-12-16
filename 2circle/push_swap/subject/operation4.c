/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:22 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/16 16:49:36 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_operation(t_stack *stack)
{
	int	tmp;

	if (!(stack) || !(stack->next))
		return ;
	tmp = stack->number;
	stack->number = stack->next->number;
	stack->next->number = tmp;
}

void	operation_sa(t_stack *stack_a)
{
	swap_operation(stack_a);
	write(1, "sa\n", 3);
}

void	operation_sb(t_stack *stack_b)
{
	swap_operation(stack_b);
	write(1, "sb\n", 3);
}

void	operation_ss(t_stack *stack_a, t_stack *stack_b)
{
	swap_operation(stack_a);
	swap_operation(stack_b);
	write(1, "ss\n", 3);
}
