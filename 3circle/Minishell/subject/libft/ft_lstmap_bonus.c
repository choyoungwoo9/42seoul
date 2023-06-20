/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:43:22 by yuikim            #+#    #+#             */
/*   Updated: 2023/04/02 11:59:44 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_new(t_list **temp, t_list **current_node,
				t_list **lst, void *(*f)(void *))
{
	(*temp)->content = f((*lst)->content);
	(*temp)->next = NULL;
	(*current_node) = (*temp);
	(*lst) = (*lst)->next;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*answer;
	t_list	*temp;
	t_list	*current_node;

	if (!lst)
		return (0);
	answer = (t_list *)(malloc(sizeof(t_list)));
	if (!answer)
		return (0);
	ft_put_new(&answer, &current_node, &lst, f);
	while (lst)
	{
		temp = (t_list *)(malloc(sizeof(t_list)));
		if (!temp)
		{
			ft_lstclear(&answer, del);
			return (answer);
		}
		current_node->next = temp;
		ft_put_new(&temp, &current_node, &lst, f);
	}
	return (answer);
}
