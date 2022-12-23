/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:52:41 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/17 16:25:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_max_num(t_stack *head)
{
	t_stack	*tmp_stack;
	int		max;

	max = INT32_MIN;
	tmp_stack = head;
	while (tmp_stack)
	{
		if (tmp_stack->number >= max)
			max = tmp_stack->number;
		tmp_stack = tmp_stack->next;
	}
	return (max);
}

static void	sort_three_node(t_stack **head, t_stack **tail)
{
	t_stack	*head_stack;
	int		max_num;

	max_num = find_max_num(*head);
	head_stack = *head;
	if (head_stack->number == max_num)
		operation_ra(head, tail);
	else if (head_stack->next->number == max_num)
		operation_rra(head, tail);
	head_stack = *head;
	if (head_stack->number > head_stack->next->number)
		operation_sa(*head);
}

void	sort_few_stack(t_stack **head, t_stack **tail)
{
	t_stack	*tmp_stack;
	int		length;

	length = find_list_length(*head);
	if (length > 3)
		return ;
	tmp_stack = *head;
	if (length == 0 || length == 1)
		return ;
	if (length == 2)
	{
		if ((*head)->number > (*head)->next->number)
			operation_sa(*head);
		return ;
	}
	if (length == 3)
		sort_three_node(head, tail);
}
