/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/14 20:48:34 by youngwch         ###   ########.fr       */
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

int	count_rb(t_stack *b_head, int number)
{
	int	count;
	count = 0;
	while(b_head)
	{
		if(b_head->number == number)
			break ;
		count ++;
		b_head = b_head->next;
	}
	return count;
}

int	count_rrb(t_stack *b_tail, int number)
{
	int	count;
	count = 1;
	while(b_tail)
	{
		if(b_tail->number == number)
			break ;
		count ++;
		b_tail = b_tail->next;
	}
	return count;
}

int count_ra(t_stack *a_head, t_stack *a_tail, int number)
{
	int count;
	t_stack *tmp_stack;
	
	count = 1;
	tmp_stack = a_head;
	while(tmp_stack)
	{
		if(tmp_stack->next)
		{
			if(tmp_stack->number < tmp_stack->next->number) //정상적인 상황
			{
				if(tmp_stack->number < number && tmp_stack->next->number > number)
				{//사잇값으로 착 들어왔을때
					break;
				}
			}
			else//최댓값 -> 최솟값으로 갔을때
			{
				if(tmp_stack->number < number || tmp_stack->next->number > number)
				{
					break;
				}
			}
		}
		if(!(tmp_stack->next))
		{
			count = 0;
			break ;
		}
		count ++;
		tmp_stack = tmp_stack->next;
	}
	return count;
}

void	rotate_and_push(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail)
{
	t_stack	*tmp_stack;
	int		min_oper_count;
	int		now_oper_count;
	int		rb_rrb_count;
	int		ra_rra_count;
	while(*b_head)
	{
		//print_stack(*a_head, *a_tail, *b_head, *b_tail);
		tmp_stack = *b_head;
		min_oper_count = INT32_MAX;
		while(tmp_stack)
		{
			//printf("\nnow num : %d\n", tmp_stack->number);
			//중간보다 위의 경우
			if(count_rb(*b_head, tmp_stack->number) <= count_rrb(*b_tail, tmp_stack->number))
				rb_rrb_count = count_rb(*b_head, tmp_stack->number);
			else //중간보다 아래의 경우
				rb_rrb_count = count_rrb(*b_tail, tmp_stack->number) * -1;
			ra_rra_count = count_ra(*a_head, *a_tail, tmp_stack->number);
			if(find_list_length(*a_head) - ra_rra_count < ra_rra_count)
				ra_rra_count = (find_list_length(*a_head) - ra_rra_count) * -1;
			//printf("rbrrb_count : %d ra_rra_count : %d\n", rb_rrb_count, ra_rra_count);
	
			now_oper_count = abs(rb_rrb_count) + abs(ra_rra_count);
			//printf("now_oper_count : %d\n", now_oper_count);
			if(min_oper_count > now_oper_count)
				min_oper_count = now_oper_count;
			tmp_stack = tmp_stack->next;
		}
		//find and print
		tmp_stack = *b_head;
		while(tmp_stack)
		{
			//중간보다 위의 경우
			if(count_rb(*b_head, tmp_stack->number) <= count_rrb(*b_tail, tmp_stack->number))
				rb_rrb_count = count_rb(*b_head, tmp_stack->number);
			else //중간보다 아래의 경우
				rb_rrb_count = count_rrb(*b_tail, tmp_stack->number) * -1;

			ra_rra_count = count_ra(*a_head, *a_tail, tmp_stack->number);
			if(find_list_length(*a_head) - ra_rra_count < ra_rra_count)
				ra_rra_count = (find_list_length(*a_head) - ra_rra_count) * -1;

			now_oper_count = abs(rb_rrb_count) + abs(ra_rra_count);
			if(min_oper_count == now_oper_count)
			{
				while(ra_rra_count)
				{
					if(ra_rra_count > 0)
					{
						printf("ra\n");
						operation_ra(a_head, a_tail);
						ra_rra_count --;
					}
					else
					{
						printf("rra\n");
						operation_rra(a_head, a_tail);
						ra_rra_count ++;	
					}
				}
				while(rb_rrb_count)
				{
					if(rb_rrb_count > 0)
					{
						printf("rb\n");
						operation_rb(b_head, b_tail);
						rb_rrb_count --;
					}
					else
					{
						printf("rrb\n");
						operation_rrb(b_head, b_tail);
						rb_rrb_count ++;	
					}
				}
				//printf("I CHOOSE %d\n", (*b_head)->number);
				printf("pa\n");
				operation_pa(a_head, a_tail, b_head, b_tail);
				break ;
			}
			tmp_stack = tmp_stack->next;
		}
	}
}

void rotate_a(t_stack **a_head, t_stack **a_tail)
{
	t_stack *tmp_stack;
	int ra_rra_count;
	tmp_stack = *a_head;

	ra_rra_count = 1;
	if(!tmp_stack)
		return ;
	while(tmp_stack)
	{
		if(tmp_stack->next)
		{
			if(tmp_stack->number > tmp_stack->next->number)
			{				
				break ;
			}
		}
		else
		{
			ra_rra_count = 0;
		}
		ra_rra_count ++;
		tmp_stack = tmp_stack->next;
	}
	if(ra_rra_count > find_list_length(*a_head) - ra_rra_count)
	{
		ra_rra_count = (find_list_length(*a_head) - ra_rra_count) * -1;
	}
	while(ra_rra_count)
	{
		if(ra_rra_count > 0)
		{
			printf("ra\n");
			operation_ra(a_head, a_tail);
			ra_rra_count --;
		}
		else
		{
			printf("rra\n");
			operation_rra(a_head, a_tail);
			ra_rra_count ++;
		}
	}
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
	rotate_a(a_head, a_tail);
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
	greedy_algo(&stack_head_a, &stack_tail_a); //인자 없을때 처리 필요
	//system("leaks a.out");	
}