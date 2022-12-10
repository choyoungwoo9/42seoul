/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:32 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/09 15:15:28 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	operation_rra(t_stack **a_head, t_stack **a_tail)
{
	int	tmp_num;
	
	if (!(*a_head) || !(*a_tail))
		return ;
	tmp_num = (*a_tail)->number;
	pop_bot(a_head, a_tail);
	push_top(a_head, a_tail, tmp_num);
}

void	operation_rrb(t_stack **b_head, t_stack **b_tail)
{
	int	tmp_num;
	
	if (!(*b_head) || !(*b_tail))
		return ;
	tmp_num = (*b_tail)->number;
	pop_bot(b_head, b_tail);
	push_top(b_head, b_tail, tmp_num);
}

void	operation_rrr(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	operation_rra(a_head, a_tail);
	operation_rrb(b_head, b_tail);
}