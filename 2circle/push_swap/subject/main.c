/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/12 19:25:33 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_push_argv(char *argv, t_stack_root *root)
{
	int	value;

	if (!is_integer(argv, &value))
		return (0);
	if (is_duplicated(value, root->head_a))
		return (0);
	push_bot(&root->head_a, &root->tail_a, value);
	return (1);
}

void	greedy_algo(t_stack_root *root)
{
	partition(root);
	sort_few_stack(&root->head_a, &root->tail_a);
	rotate_and_push(root);
	align_stack(root);
}

int	main(int argc, char **argv)
{
	t_stack_root	root;

	root.head_a = NULL;
	root.tail_a = NULL;
	root.head_b = NULL;
	root.tail_b = NULL;
	if (argc < 2)
		return (0);
	while (*(++argv))
	{
		if (!check_push_argv(*argv, &root))
		{
			write(1, "Error\n", 6);
			return (0);
		}
	}
	sort_few_stack(&root.head_a, &root.tail_a);
	sorted_check(root.head_a, root.head_b);
	greedy_algo(&root);
}
