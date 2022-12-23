/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:59:54 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/17 16:47:58 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_stack
{
	int				number;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_stack_root
{
	t_stack	*head_a;
	t_stack	*tail_a;
	t_stack	*head_b;
	t_stack	*tail_b;
}	t_stack_root;

void	push_top(t_stack **head, t_stack **tail, int number);
void	push_bot(t_stack **head, t_stack **tail, int number);
void	pop_top(t_stack **head, t_stack **tail);
void	pop_bot(t_stack **head, t_stack **tail);
void	operation_sa(t_stack *stack_a);
void	operation_sb(t_stack *stack_b);
void	operation_ss(t_stack *stack_a, t_stack *stack_b);
void	operation_pa(t_stack **a_head,
			t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_pb(t_stack **a_head,
			t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_ra(t_stack **a_head, t_stack **a_tail);
void	operation_rb(t_stack **b_head, t_stack **b_tail);
void	operation_rr(t_stack **a_head,
			t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
void	operation_rra(t_stack **a_head, t_stack **a_tail);
void	operation_rrb(t_stack **b_head, t_stack **b_tail);
void	operation_rrr(t_stack **a_head,
			t_stack **a_tail, t_stack **b_head, t_stack **b_tail);
int		is_integer(char *argv, int *value);
int		is_duplicated(int value, t_stack *head);
int		find_list_length(t_stack *head);
void	quick_sort(int *ar, int length);
int		ft_abs(int num);
int		count_rb(t_stack *b_head, int number);
int		count_ra(t_stack *a_head, int number);
void	partition(t_stack_root *root);
void	align_stack(t_stack_root *root);
int		find_pivot(t_stack *a_head);
void	rotate_and_push(t_stack_root *root);
void	sorted_check(t_stack *a_head, t_stack *b_head);
void	sort_few_stack(t_stack **head, t_stack **tail);
#endif