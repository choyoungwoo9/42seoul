/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeong-u <joyeong-u@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/08 23:01:52 by joyeong-u        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"

void	push_top(t_stack **head, int number)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(t_stack));
	new_stack->number = number;
	new_stack->next = *head;
	new_stack->prev = NULL;
	*head = new_stack;
}

void	pust_bot(t_stack **tail, int number)
{
	t_stack *new_stack;
	
	new_stack = (t_stack *)malloc(sizeof(t_stack));
	new_stack->number = number;
	new_stack->next = NULL;
	new_stack->prev = 
}



int main(int argc, char **argv)
{
	t_stack	*stack_head;
	t_stack	*stack_head;

	stack_head = NULL;

	push_top(&stack_head, 5);
	push_top(&stack_head, 4);
	push_top(&stack_head, 3);
	push_top(&stack_head, 2);
	push_top(&stack_head, 1);

	//1 -> 2 -> 3 -> 4 -> 5

	push_bot(&stack_head, 10);
	//pop_top(&stack_head);
	//pop_bot(&stack_head);
	while(stack_head)
	{
		printf("%d\n", stack_head->number);
		stack_head = stack_head->next;
	}
}