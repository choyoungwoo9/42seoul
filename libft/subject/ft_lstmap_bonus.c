/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:01:57 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/15 19:00:26 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// static void	free_all_lst(t_list *start_lst, void (*del)(void *))
// {
// 	t_list	*tmp_lst;

// 	while (start_lst != (t_list *)-1)
// 	{
// 		tmp_lst = start_lst;
// 		start_lst = tmp_lst -> next;
// 		del(tmp_lst -> content);
// 		free(tmp_lst);
// 	}
// 	return ;
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start_lst;
	t_list	*tmp_lst;
	t_list	*tmp2_lst;

	start_lst = (t_list *)(malloc(sizeof(t_list)));
	if (start_lst == 0)
		return (0);
	start_lst -> content = f(lst -> content);
	lst = lst -> next;
	tmp_lst = start_lst;
	while (lst)
	{
		tmp2_lst = (t_list *)(malloc(sizeof(t_list)));
		if (tmp2_lst == (t_list *)('\0'))
		{
			ft_lstclear(&start_lst, del);
			return (0);
		}
		tmp_lst -> next = tmp2_lst;
		tmp_lst = tmp2_lst;
		tmp_lst -> content = f(lst -> content);
		lst = lst -> next;
		tmp_lst -> next = (void *)(-1);
	}
	tmp_lst -> next = 0;
	return (start_lst);
}
