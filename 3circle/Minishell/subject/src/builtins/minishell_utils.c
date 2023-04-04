/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:25:04 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/27 20:56:35 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	show_error(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	perror(cmd);
}

char	*get_env_value(char **envp, char *key)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			return (&envp[i][ft_strlen(key) + 1]);
		i++;
	}
	return (NULL);
}

void	free_dptr(char **dptr, int opt)
{
	int	i;

	i = opt;
	while (dptr[i])
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
}

char	*str_total_join(char **words, char *operator)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = ft_strdup(words[i]);
	i++;
	while (words[i])
	{
		temp = str;
		str = ft_strjoin(str, operator);
		free(temp);
		temp = str;
		str = ft_strjoin(str, words[i]);
		free(temp);
		i++;
	}
	return (str);
}

char	**dptr_dup(char **dptr)
{
	int		i;
	char	**new_dptr;
	int		size;

	new_dptr = NULL;
	i = -1;
	size = get_dptr_size(dptr);
	if (dptr)
	{
		new_dptr = malloc(sizeof(char *) * (size + 1));
		if (new_dptr)
		{
			new_dptr[size] = NULL;
			while (++i < size)
				new_dptr[i] = ft_strdup(dptr[i]);
		}
	}
	return (new_dptr);
}
