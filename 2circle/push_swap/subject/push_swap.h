/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:59:54 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/15 19:13:19 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> ////////////////

// typedef struct s_stack_manager
// {
// 	t_stack	*stack_head_a;
// 	t_stack	*stack_tail_a;
// 	t_stack	*stack_head_b;
// 	t_stack	*stack_tail_b;
	
// }	t_stack_manager;


typedef	struct s_stack
{
	int	number;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

void	print_stack(t_stack	*head_a, t_stack *tail_a, t_stack *head_b, t_stack *tail_b);

void	push_top(t_stack **head, t_stack **tail, int number);
void	push_bot(t_stack **head, t_stack **tail, int number);
void	pop_top(t_stack **head, t_stack **tail);
void	pop_bot(t_stack **head, t_stack **tail);

void	operation_sa(t_stack *stack_a);
void	operation_sb(t_stack *stack_b);
void	operation_ss(t_stack *stack_a, t_stack *stack_b);
void	operation_pa(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_pb(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_ra(t_stack **a_head, t_stack **a_tail);
void	operation_rb(t_stack **b_head, t_stack **b_tail);
void	operation_rr(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_rra(t_stack **a_head, t_stack **a_tail);
void	operation_rrb(t_stack **b_head, t_stack **b_tail);
void	operation_rrr(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);

int	is_integer(char *argv, int *value);
int	is_duplicated(int value, t_stack *head);

int	find_list_length(t_stack *head);
void	quick_sort(int *ar, int length);
int	ft_abs(int num);

int	count_rb(t_stack *b_head, int number);
int count_ra(t_stack *a_head, int number);

void	partition(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void align_stack(t_stack **a_head, t_stack **a_tail);

int	find_pivot(t_stack *a_head);
void	rotate_and_push(t_stack **a_head, t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
#endif