/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/12 16:56:04 by youngwch         ###   ########.fr       */
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

void	partition(int pivot, t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	t_stack	*tmp_node;
	int		tmp;
	int		count;
	
	tmp_node = *a_head;
	count = find_list_length(*a_head);
	while(--count >= 0)
	{
		if(*a_head == NULL)
			break;
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

int	find_ra_count(t_stack *a_head, int num)
{
	int	length;
	t_stack *tmp_node;
	int count; //ra = 양수 rra = 음수

	count = 0;
	tmp_node = a_head;
	length = find_list_length(tmp_node);
	while(tmp_node)
	{
		if(!(tmp_node->next))
		{
			if(tmp_node->number >= a_head->number) //마지막
				if()

			break;
		}
		if(tmp_node)
		tmp_node = tmp_node->next;
	}
	
}

void	rotate_and_push(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	int	oper_count;
	int length;
	int rb_count;
	t_stack	*tmp_node;

	length = find_list_length(*b_head);
	while(*b_head)
	{
		tmp_node = *b_head;
		rb_count = 0;
		while(tmp_node)
		{
			//pa sa ra sb rb rrb rra
			oper_count = rb_count + find_ra_count(*a_head, tmp_node->number);
			tmp_node = tmp_node->next;
			// if(rb_count <= length/2)
			// 	rb_count ++;
			// else
			// 	rb_count --;
		}
		
	}
}


void	greedy_algo(t_stack **a_head, t_stack **a_tail)
{
	t_stack	*b_head;
	t_stack	*b_tail;
	
	b_head = NULL;
	b_tail = NULL;
	int	pivot;

	pivot = find_pivot(*a_head);
	printf("pivot : %d\n", pivot);
	partition(pivot, a_head, a_tail, &b_head, &b_tail);
	rotate_and_push(a_head, a_tail, &b_head, &b_tail);
	print_stack(*a_head, *a_tail, b_head, b_tail);
	
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
	greedy_algo(&stack_head_a, &stack_tail_a);
	//push_bot(&stack_head_a);
	//system("leaks a.out");	
}