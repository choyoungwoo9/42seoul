/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/08 17:44:33 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_top(t_queue **head, int number)
{
	t_queue	*new_queue;

	new_queue = (t_queue *)malloc(sizeof(t_queue));
	new_queue->number = number;
	new_queue->next = *head;
	*head = new_queue;
}


int main(int argc, char **argv)
{
	t_queue	*list_queue_a_head;
	int num;

	num = 5;
	list_queue_a_head = NULL;

	push_top(&list_queue_a_head, num);
	push_bot(&list_queue_a_head);
	pop_top(&list_queue_a_head);
	pop_bot(&list_queue_a_head);
}