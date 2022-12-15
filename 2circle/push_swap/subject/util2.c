/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:41:39 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 17:38:48 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_list_length(t_stack *head)
{
	int length;

	length = 0;
	while(head)
	{
		length ++;
		head = head->next;
	}
	return length;
}

//now bubble
void	quick_sort(int *ar, int length)
{
	int tmp;

	for(int i = 0; i < length; i ++)
	{
		for(int j = 0; j < length-1-i; j ++)
		{
			if(ar[j] > ar[j+1])
			{
				tmp = ar[j];
				ar[j] = ar [j + 1];
				ar[j + 1] = tmp;
			}
		}
	}
}

int	ft_abs(int num)
{
	long long lnum;
	
	lnum = num;
	if(lnum < 0)
		lnum = lnum * -1;
	return lnum;
}

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
	if(length)
		pivot = *(ar + length/2);
	free(ar);
	return pivot;
}