/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/09 15:15:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	operation_ra(t_stack **a_head, t_stack **a_tail)
{
	int	tmp_num;
	
	if (!(*a_head) || !(*a_tail))
		return ;
	tmp_num = (*a_head)->number;
	pop_top(a_head, a_tail);
	push_bot(a_head, a_tail, tmp_num);
}

void	operation_rb(t_stack **b_head, t_stack **b_tail)
{
	int	tmp_num;
	
	if (!(*b_head) || !(*b_tail))
		return ;
	tmp_num = (*b_head)->number;
	pop_top(b_head, b_tail);
	push_bot(b_head, b_tail, tmp_num);
}

void	operation_rr(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	operation_ra(a_head, a_tail);
	operation_rb(b_head, b_tail);
}