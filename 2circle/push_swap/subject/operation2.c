/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:45:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 17:03:05 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_operation(t_stack **head, t_stack **tail)
{
	int	tmp_num;

	if (!(*head) || !(*tail))
		return ;
	tmp_num = (*head)->number;
	pop_top(head, tail);
	push_bot(head, tail, tmp_num);
}

void	operation_ra(t_stack **a_head, t_stack **a_tail)
{
	rotate_operation(a_head, a_tail);
	printf("ra\n");
}

void	operation_rb(t_stack **b_head, t_stack **b_tail)
{
	rotate_operation(b_head, b_tail);
	printf("rb\n");
}

void	operation_rr(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	rotate_operation(a_head, a_tail);
	rotate_operation(b_head, b_tail);
	printf("rr\n");
}