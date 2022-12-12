/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:53:45 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/12 16:00:06 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_pivot(t_stack *a_head)
{
	t_stack *tmp_node;
	int	length;
	int	*ar;
	int pivot;

	tmp_node = a_head;
	length = find_list_length(a_head);
	ar = (int *)malloc(sizeof(int) * length);
	tmp_node = a_head;
	length = 0;
	while(tmp_node)
	{
		*(ar + length) = tmp_node->number;
		tmp_node = tmp_node->next;
		length ++;
	}
	quick_sort(ar, length);
	pivot = ar[length/2];
	free(ar);
	return pivot;
}