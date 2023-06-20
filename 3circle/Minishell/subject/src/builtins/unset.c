/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:06:16 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/31 13:34:06 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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

int	unset(char **args, char **envp)
{
	int	ret;

	ret = 0;
	while (*(++args))
	{
		if (*args[0] != '_' && !ft_isalpha(*args[0]))
		{
			print_builtin_error(*args);
			ret = 1;
			continue ;
		}
		if (!get_env_value(envp, *args))
			continue ;
		remove_env(*args, envp);
	}
	return (ret);
}
