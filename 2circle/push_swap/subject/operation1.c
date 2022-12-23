/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:22 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/17 15:43:36 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_operation(t_stack **a_head,
	t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	int	tmp_num;

	if (!(*b_head) || !(*b_tail))
		return ;
	tmp_num = (*b_head)->number;
	pop_top(b_head, b_tail);
	push_top(a_head, a_tail, tmp_num);
}

void	operation_pa(t_stack **a_head,
	t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	push_operation(a_head, a_tail, b_head, b_tail);
	write(1, "pa\n", 3);
}

void	operation_pb(t_stack **a_head,
	t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	push_operation(b_head, b_tail, a_head, a_tail);
	write(1, "pb\n", 3);
}
