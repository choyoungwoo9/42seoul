/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:41:39 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/12 15:44:12 by youngwch         ###   ########.fr       */
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