/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:10:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/16 17:29:05 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_push_argv(char *argv, t_stack_root *root)
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
	while (*(++argv))
	{
		if (!check_push_argv(*argv, &root))
		{
			printf("Error\n");
			return (0);
		}
	}
	greedy_algo(&root);
	//system("Leaks push_swap");
}
