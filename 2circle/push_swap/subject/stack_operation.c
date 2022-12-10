/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:16:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/10 13:24:31 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_top(t_stack **head, t_stack **tail, int number)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(t_stack));
	new_stack->number = number;
	new_stack->next = *head;
	new_stack->prev = NULL;
	if(*head)
		(*head)->prev = new_stack;
	else
		*tail = new_stack;
	*head = new_stack;
}

void	push_bot(t_stack **head, t_stack **tail, int number)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(t_stack));
	new_stack->number = number;
	new_stack->next = NULL;
	new_stack->prev = *tail;
	if(*tail) //이미 스택이 존재할 경우
		(*tail)->next = new_stack;
	else //처음으로 push_bot을 했을 경우
		*head = new_stack;
	*tail = new_stack;
}

void	pop_top(t_stack **head, t_stack **tail)
{
	t_stack	*tmp;
	
	if(!*head || !*tail)
		return;
	tmp = *head;
	*head = (*head)->next;
	free(tmp);
	if(*head)
		(*head)->prev = NULL;
	else
		*tail = NULL;
}

void	pop_bot(t_stack **head, t_stack **tail)
{
	t_stack	*tmp;
	
	if(!*head || !*tail)
		return;
	tmp = *tail;
	*tail = (*tail)->prev;
	free(tmp);
	if(*tail)
		(*tail)->next = NULL;
	else
		*head = NULL;
}