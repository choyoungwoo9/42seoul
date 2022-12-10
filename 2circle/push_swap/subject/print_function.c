/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:13:32 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/10 14:13:45 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack	*head_a, t_stack *tail_a, t_stack *head_b, t_stack *tail_b)
{
	t_stack *tmp = head_a;
	printf("\n앞에서 시작 \n");
	printf("a 의 값은 ...\n");
	while(tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->next;
	}
	printf("\n");

	printf("b 의 값은 ...\n");
	tmp = head_b;
	while(tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->next;
	}
	printf("\n");

	tmp = tail_a;
	printf("\n뒤에서 시작 \n");
	printf("a 의 값은 ...\n");
	while(tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->prev;
	}
	printf("\n");
	printf("b 의 값은 ...\n");
	tmp = tail_b;
	while(tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->prev;
	}
	printf("\n");
}