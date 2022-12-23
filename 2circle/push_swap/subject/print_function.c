/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:13:32 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/17 21:57:27 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"

void	print_stack(t_stack_root root)
{
	t_stack	*tmp;//ddfadfasd

	tmp = root.head_a;
	printf("\n앞에서 시작 \n");
	printf("a 의 값은 ...\n");
	while (tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->next;
	}
	printf("\n");
	printf("b 의 값은 ...\n");
	tmp = root.head_b;
	while (tmp)
	{
		printf("%d -> ", tmp->number);
		tmp = tmp->next;
	}
	printf("\n");
}
