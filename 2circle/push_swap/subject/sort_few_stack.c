/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_few_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:52:41 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/16 20:02:02 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/// pass by ref value  
void	sort_few_stack(t_stack *head)
{
	int length = find_list_length(head);
	t_stack	*tmp_stack;

	if(length > 3)
		return ;
	tmp_stack = head;
	if(length == 0 || length == 1)
		return ;
	if(length == 2)
	{
		if(head->number > head->next->number)
			operation_sa(head);
	}
	while(head)
	{
		
	}
}