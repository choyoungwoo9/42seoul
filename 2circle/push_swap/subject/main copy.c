/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/09 15:23:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"
#include "operation1.c"
#include "operation2.c"
#include "operation3.c"
#include "stack_operation.c"

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

	push_top(&stack_head_a, &stack_tail_a, 5);
	push_top(&stack_head_a, &stack_tail_a, 4);
	push_top(&stack_head_a, &stack_tail_a, 3);
	push_top(&stack_head_a, &stack_tail_a, 2);
	push_top(&stack_head_a, &stack_tail_a, 1);

	push_top(&stack_head_b, &stack_tail_b, 5);
	push_top(&stack_head_b, &stack_tail_b, 4);
	push_top(&stack_head_b, &stack_tail_b, 3);
	push_top(&stack_head_b, &stack_tail_b, 2);
	push_top(&stack_head_b, &stack_tail_b, 1);
	//1 -> 2 -> 3 -> 4 -> 5
	
	push_bot(&stack_head_a, &stack_tail_a, 6);
	push_bot(&stack_head_a, &stack_tail_a, 7);
	push_bot(&stack_head_a, &stack_tail_a, 8);
	push_bot(&stack_head_a, &stack_tail_a, 9);
	push_bot(&stack_head_a, &stack_tail_a, 10);
	
	push_bot(&stack_head_b, &stack_tail_b, 6);
	push_bot(&stack_head_b, &stack_tail_b, 7);
	push_bot(&stack_head_b, &stack_tail_b, 8);
	push_bot(&stack_head_b, &stack_tail_b, 9);
	push_bot(&stack_head_b, &stack_tail_b, 10);
	//1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
	printf("\ndefault\n");
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\npop_top\n");
	pop_top(&stack_head_a, &stack_tail_a);
	pop_top(&stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\npop_bot\n");
	pop_bot(&stack_head_a, &stack_tail_a);
	pop_bot(&stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);
	
	printf("\nsa\n");
	operation_sa(stack_head_a);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nsb\n");
	operation_sb(stack_head_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nss\n");
	operation_ss(stack_head_a, stack_head_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\npa\n");
	operation_pa(&stack_head_a, &stack_tail_a, &stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\npb\n");
	operation_pb(&stack_head_a, &stack_tail_a, &stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nra\n");
	operation_ra(&stack_head_a, &stack_tail_a);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nrb\n");
	operation_rb(&stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nrr\n");
	operation_rr(&stack_head_a, &stack_tail_a, &stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nrra\n");
	operation_rra(&stack_head_a, &stack_tail_a);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nrrb\n");
	operation_rrb(&stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);

	printf("\nrrr\n");
	operation_rrr(&stack_head_a, &stack_tail_a, &stack_head_b, &stack_tail_b);
	print_stack(stack_head_a, stack_tail_a, stack_head_b, stack_tail_b);
	//system("leaks a.out");	
}