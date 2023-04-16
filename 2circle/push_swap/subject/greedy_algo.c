/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:53:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/12 19:26:15 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_oper_count(t_stack *a_head, t_stack *b_head)
{
	t_stack	*tmp_stack;
	int		now_oper_count;
	int		min_oper_count;

	tmp_stack = b_head;
	min_oper_count = INT32_MAX;
	while (tmp_stack)
	{
		now_oper_count = ft_abs(count_ra(a_head, tmp_stack->number))
			+ ft_abs(count_rb(b_head, tmp_stack->number));
		if (min_oper_count > now_oper_count)
			min_oper_count = now_oper_count;
		tmp_stack = tmp_stack->next;
	}
	return (min_oper_count);
}

static void	dup_optimizing(t_stack_root *root,
	int *ra_rra_count, int *rb_rrb_count)
{
	if ((*ra_rra_count) * (*rb_rrb_count) < 0)
		return ;
	if (*ra_rra_count > 0 && *rb_rrb_count > 0)
	{
		while (!*ra_rra_count || !*rb_rrb_count)
		{
			operation_rr(&root->head_a, &root->tail_a,
				&root->head_a, &root->tail_a);
			ra_rra_count --;
			rb_rrb_count --;
		}
	}
	if (*ra_rra_count < 0 && *rb_rrb_count < 0)
	{
		while (!*ra_rra_count || !*rb_rrb_count)
		{
			operation_rrr(&root->head_a, &root->tail_a,
				&root->head_a, &root->tail_a);
			ra_rra_count ++;
			rb_rrb_count ++;
		}
	}
}

static void	rotate_min_oper(t_stack_root *root
	, int ra_rra_count, int rb_rrb_count)
{
	while (ra_rra_count)
	{
		if (ra_rra_count > 0)
			operation_ra(&(root->head_a), &root->tail_a);
		else
			operation_rra(&root->head_a, &root->tail_a);
		ra_rra_count += -1 * (ra_rra_count > 0) + (ra_rra_count < 0);
	}
	while (rb_rrb_count)
	{
		if (rb_rrb_count > 0)
			operation_rb(&root->head_b, &root->tail_b);
		else
			operation_rrb(&root->head_b, &root->tail_b);
		rb_rrb_count += -1 * (rb_rrb_count > 0) + (rb_rrb_count < 0);
	}
}

static void	greedy_rotate_push(t_stack_root *root, int min_oper_count)
{
	t_stack	*tmp_stack;
	int		ra_rra_count;
	int		rb_rrb_count;
	int		now_oper_count;

	tmp_stack = root->head_b;
	while (tmp_stack)
	{
		ra_rra_count = count_ra(root->head_a, tmp_stack->number);
		rb_rrb_count = count_rb(root->head_b, tmp_stack->number);
		now_oper_count = ft_abs(count_ra(root->head_a, tmp_stack->number))
			+ ft_abs(count_rb(root->head_b, tmp_stack->number));
		if (min_oper_count == now_oper_count)
		{
			dup_optimizing(root, &ra_rra_count, &rb_rrb_count);
			rotate_min_oper(root, ra_rra_count, rb_rrb_count);
			break ;
		}
		tmp_stack = tmp_stack->next;
	}
	operation_pa(&root->head_a, &root->tail_a, &root->head_b, &root->tail_b);
}

void	rotate_and_push(t_stack_root *root)
{
	while (root->head_b)
		greedy_rotate_push(root,
			find_min_oper_count(root->head_a, root->head_b));
}
