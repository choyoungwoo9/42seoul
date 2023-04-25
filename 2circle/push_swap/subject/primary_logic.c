/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:52:36 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/19 20:16:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	partition(t_stack_root *root)
{
	t_stack	*tmp_node;
	int		pivot;

	pivot = find_pivot(root->head_a);
	tmp_node = root->head_a;
	while (find_list_length(root->head_a) > find_list_length(root->head_b)
		&& find_list_length(root->head_a) > 3)
	{
		if (tmp_node->number <= pivot)
			operation_pb(&root->head_a,
				&root->tail_a, &root->head_b, &root->tail_b);
		else
			operation_ra(&root->head_a, &root->tail_a);
		tmp_node = root->head_a;
	}
	while (find_list_length(root->head_a) > 3)
	{
		operation_pb(&root->head_a,
			&root->tail_a, &root->head_b, &root->tail_b);
		tmp_node = root->head_a;
	}
}

int	find_rotate_count(t_stack *a_head)
{
	t_stack	*tmp_stack;
	int		ra_rra_count;

	tmp_stack = a_head;
	ra_rra_count = 1;
	while (tmp_stack)
	{
		if (tmp_stack->next)
		{
			if (tmp_stack->number > tmp_stack->next->number)
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
	if (ra_rra_count > find_list_length(a_head) - ra_rra_count)
		ra_rra_count = (find_list_length(a_head) - ra_rra_count) * -1;
	return (ra_rra_count);
}

static void	rotate_a(int ra_rra_count, t_stack **a_head, t_stack **a_tail)
{
	while (ra_rra_count)
	{
		if (ra_rra_count > 0)
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

void	align_stack(t_stack_root *root)
{
	t_stack	*tmp_stack;
	int		ra_rra_count;

	tmp_stack = root->head_a;
	if (!tmp_stack)
		return ;
	ra_rra_count = find_rotate_count(tmp_stack);
	rotate_a(ra_rra_count, &root->head_a, &root->tail_a);
}
