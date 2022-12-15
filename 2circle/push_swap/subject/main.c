/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 18:24:13 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_push_argv(char *argv, t_stack **head, t_stack **tail)
{
	int	value;

	if(!is_integer(argv, &value))
		return 0;
	if(is_duplicated(value, *head))
		return 0;
	//printf("%d, ", value);
	push_bot(head, tail, value);
	return 1;
}

void	greedy_algo(t_stack **a_head, t_stack **a_tail)
{
	t_stack	*b_head;
	t_stack	*b_tail;
	
	b_head = NULL;
	b_tail = NULL;
	//print_stack(*a_head, *a_tail, b_head, b_tail);
	partition(a_head, a_tail, &b_head, &b_tail);
	//print_stack(*a_head, *a_tail, b_head, b_tail);
	rotate_and_push(a_head, a_tail, &b_head, &b_tail);
	//print_stack(*a_head, *a_tail, b_head, b_tail);
	align_stack(a_head, a_tail);
	//print_stack(*a_head, *a_tail, b_head, b_tail);
	//free_all_list(b_head); //나중에는 결국 b_head가 널일때까지 수행하므로 필요 없을 예정
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
	//printf("\n");
	greedy_algo(&stack_head_a, &stack_tail_a); //인자 없을때 처리 필요
	//system("leaks a.out");	
}