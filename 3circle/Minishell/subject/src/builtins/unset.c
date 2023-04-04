/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:06:16 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/28 15:22:51 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	remove_env(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			break ;
		i++;
	}
	free(envp[i]);
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

int	unset(char *key, char **envp)
{
	if (!key || !get_env_value(envp, key))
		return (1);
	remove_env(key, envp);
	return (0);
}
