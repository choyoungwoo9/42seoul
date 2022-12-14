/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/14 18:46:21 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"
#include "operation1.c"
#include "operation2.c"
#include "operation3.c"
#include "util.c"
#include "util2.c"
#include "stack_operation.c"
#include "print_function.c"
#include "greedy_algo.c"

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

void	partition(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	t_stack	*tmp_node;
	int		tmp;
	int		count;
	int		pivot;

	pivot = find_pivot(*a_head);

	tmp_node = *a_head;
	count = find_list_length(*a_head);
	while(--count >= 0)
	{
		// if(*a_head == NULL)
		// 	break;
		tmp = tmp_node->number;
		if(tmp < pivot)
		{
			operation_pb(a_head, a_tail, b_head, b_tail);
			printf("pb\n");
		}
		else
		{
			operation_ra(a_head, a_tail);
			printf("ra\n");
		}
		tmp_node = *a_head;
	}
	while(tmp_node)
	{
		operation_pb(a_head, a_tail, b_head, b_tail);
		printf("pb\n");
		tmp_node = *a_head;
	}
}

void	rotate_and_push(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	
}


void	greedy_algo(t_stack **a_head, t_stack **a_tail)
{
	t_stack	*b_head;
	t_stack	*b_tail;
	
	b_head = NULL;
	b_tail = NULL;

	partition(a_head, a_tail, &b_head, &b_tail);
	print_stack(*a_head, *a_tail, b_head, b_tail);
	rotate_and_push(a_head, a_tail, &b_head, &b_tail);
	print_stack(*a_head, *a_tail, b_head, b_tail);
	free_all_list(b_head); //나중에는 결국 b_head가 널일때까지 수행하므로 필요 없을 예정
}

int main(int argc, char **argv)
{
	t_stack	*stack_head_a;
	t_stack	*stack_tail_a;

	stack_head_a = NULL;
	stack_tail_a = NULL;
	while(*(++argv))
	{
		if(!check_push_argv(*argv, &stack_head_a, &stack_tail_a))
		{
			printf("Error\n");
			return (0);
		}
	}
	//print_stack(stack_head_a,stack_tail_a,stack_head_b,stack_tail_b);
	greedy_algo(&stack_head_a, &stack_tail_a); //인자 없을때 처리 필요
	system("leaks a.out");	
}