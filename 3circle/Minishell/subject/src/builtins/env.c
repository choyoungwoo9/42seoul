/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:46:29 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/31 13:33:40 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	env(char **args, char **envp)
{
	int	i;

	while (*(++args))
	{
		if (!is_same_str(*args, "env"))
		{
			printf("%s\n", *args);
			ft_putstr_fd("option not implement\n", 2);
			return (1);
		}
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}
