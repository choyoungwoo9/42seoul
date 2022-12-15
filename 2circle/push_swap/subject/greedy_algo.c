/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:53:45 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 19:13:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int find_min_oper_count(t_stack	*tmp_stack, t_stack *a_head, t_stack *b_head)
{
	int		ra_rra_count;
	int		rb_rrb_count;
	int		now_oper_count;
	int		min_oper_count;

	min_oper_count = INT32_MAX;
	while(tmp_stack)
	{
		ra_rra_count = count_ra(a_head, tmp_stack->number);
		rb_rrb_count = count_rb(b_head, tmp_stack->number);
		//printf("rbrrb_count : %d ra_rra_count : %d\n", rb_rrb_count, ra_rra_count);
		now_oper_count = ft_abs(rb_rrb_count) + ft_abs(ra_rra_count);
		//printf("now_oper_count : %d\n", now_oper_count);
		if(min_oper_count > now_oper_count)
			min_oper_count = now_oper_count;
		tmp_stack = tmp_stack->next;
	}
	return min_oper_count;
}

// static int is_min_stack(t_stack *a_head, t_stack *b_head, t_stack *tmp_stack, int min_oper_count)
// {
// 	int		ra_rra_count;
// 	int		rb_rrb_count;
// 	int		now_oper_count;

// 	ra_rra_count = count_ra(a_head, tmp_stack->number);
// 	rb_rrb_count = count_rb(b_head, tmp_stack->number);
// 	now_oper_count = ft_abs(rb_rrb_count) + ft_abs(ra_rra_count);
// 	if(min_oper_count == now_oper_count)
// 		return 1;
// 	return 0;
// }

void	rotate_and_push(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	t_stack	*tmp_stack;
	int		ra_rra_count;
	int		rb_rrb_count;
	int		min_oper_count;
	int		now_oper_count;

	while(*b_head)
	{
		tmp_stack = *b_head;
		min_oper_count = find_min_oper_count(tmp_stack, *a_head, *b_head);
		while(tmp_stack)
		{ 
			ra_rra_count = count_ra(*a_head, tmp_stack->number);
			rb_rrb_count = count_rb(*b_head, tmp_stack->number);
			now_oper_count = ft_abs(rb_rrb_count) + ft_abs(ra_rra_count);
			if(min_oper_count == now_oper_count)
			{
				while(ra_rra_count)
				{
					if(ra_rra_count > 0)
						operation_ra(a_head, a_tail);	
					else
						operation_rra(a_head, a_tail);
					ra_rra_count += -1 * (ra_rra_count > 0) + (ra_rra_count < 0);
				}
				while(rb_rrb_count)
				{
					if(rb_rrb_count > 0)
						operation_rb(b_head, b_tail);
					else
						operation_rrb(b_head, b_tail);
					rb_rrb_count += -1 * (rb_rrb_count > 0) + (rb_rrb_count < 0);
				}
				break ;
			}
			tmp_stack = tmp_stack->next;
		}
		operation_pa(a_head, a_tail, b_head, b_tail);
	}
}