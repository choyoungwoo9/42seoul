/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/10 16:56:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"
#include "operation1.c"
#include "operation2.c"
#include "operation3.c"
#include "util.c"
#include "stack_operation.c"
#include "print_function.c"

int	check_push_argv(char *argv, t_stack **head, t_stack **tail)
{
	int	value;

	if(!is_integer(argv, &value))
		return 0;
	if(is_duplicated(value, *head))
		return 0;
	push_bot(head, tail, value);
	return 1;
}

int main(int argc, char **argv)
{
	t_stack	*stack_head_a;
	t_stack	*stack_tail_a;

	t_stack	*stack_head_b;
	t_stack	*stack_tail_b;

	stack_head_a = NULL;
	stack_tail_a = NULL;
	stack_head_b = NULL;
	stack_tail_b = NULL;

	while(*(++argv))
	{
		printf("argv : %s\n", *argv);
		if(!check_push_argv(*argv, &stack_head_a, &stack_tail_a))
		{
			printf("Error\n");
			return (0);
		}
	}
	print_stack(stack_head_a,stack_tail_a,stack_head_b,stack_tail_b);
	//push_bot(&stack_head_a);
	//system("leaks a.out");	
}