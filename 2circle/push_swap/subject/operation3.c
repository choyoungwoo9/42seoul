/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:32 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/16 16:50:33 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_operation(t_stack **head, t_stack **tail)
{
	int	tmp_num;

	if (!(*head) || !(*tail))
	{
		return ;
	}
	tmp_num = (*tail)->number;
	pop_bot(head, tail);
	push_top(head, tail, tmp_num);
}

void	operation_rra(t_stack **a_head, t_stack **a_tail)
{	
	reverse_rotate_operation(a_head, a_tail);
	write(1, "rra\n", 4);
}

void	operation_rrb(t_stack **b_head, t_stack **b_tail)
{
	reverse_rotate_operation(b_head, b_tail);
	write(1, "rrb\n", 4);
}

void	operation_rrr(t_stack **a_head,
	t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	reverse_rotate_operation(a_head, a_tail);
	reverse_rotate_operation(b_head, b_tail);
	write(1, "rrr\n", 4);
}
