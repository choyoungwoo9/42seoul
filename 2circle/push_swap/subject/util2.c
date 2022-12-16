/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:41:39 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/16 17:12:10 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_list_length(t_stack *head)
{
	int	length;

	length = 0;
	while (head)
	{
		length ++;
		head = head->next;
	}
	return (length);
}

void	bubble_sort(int *ar, int length)
{
	int	tmp;
	int	i;
	int	j;

	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < length - i - 1)
		{
			if (*(ar + j) > *(ar + j + 1))
			{
				tmp = *(ar + j);
				*(ar + j) = *(ar + j + 1);
				*(ar + j + 1) = tmp;
			}
			j ++;
		}
		i ++;
	}
}

int	ft_abs(int num)
{
	long long	lnum;

	lnum = num;
	if (lnum < 0)
		lnum = lnum * -1;
	return (lnum);
}

int	find_pivot(t_stack *a_head)
{
	t_stack	*tmp_node;
	int		length;
	int		*ar;
	int		pivot;

	tmp_node = a_head;
	length = find_list_length(a_head);
	ar = (int *)malloc(sizeof(int) * length);
	tmp_node = a_head;
	length = 0;
	while (tmp_node)
	{
		*(ar + length) = tmp_node->number;
		tmp_node = tmp_node->next;
		length ++;
	}
	bubble_sort(ar, length);
	if (length)
		pivot = *(ar + length / 2);
	free(ar);
	return (pivot);
}
