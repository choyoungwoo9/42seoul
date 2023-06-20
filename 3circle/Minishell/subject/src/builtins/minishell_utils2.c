/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:22:12 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/31 13:33:42 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	get_dptr_size(char **dptr)
{
	int	i;

	i = 0;
	while (dptr[i])
		i++;
	return (i);
}

void	set_env_statement(char **env_addr, char *key, char *value)
{
	char	*str;
	char	*temp;

	str = key;
	temp = str;
	str = ft_strjoin(str, "=");
	temp = str;
	str = ft_strjoin(str, value);
	free(temp);
	free(*env_addr);
	*env_addr = str;
}

char	*create_env_statement(char *key, char *value)
{
	char	*str;
	char	*temp;

	str = ft_strjoin(key, "=");
	temp = str;
	str = ft_strjoin(str, value);
	free(temp);
	return (str);
}

void	make_env_statement(char ***envp_ptr, char *key, char *value)
{
	char	*statement;

	statement = create_env_statement(key, value);
	append_dptr(envp_ptr, statement);
}

void	append_dptr(char ***dptr, char *statement)
{
	int		i;
	int		size;
	char	**new_dptr;

	if (!dptr)
		return ;
	size = get_dptr_size(*dptr) + 1;
	new_dptr = malloc(sizeof(char *) * (size + 1));
	if (new_dptr)
	{
		i = -1;
		while (++i < size - 2)
			new_dptr[i] = (*dptr)[i];
		new_dptr[size - 2] = statement;
		new_dptr[size - 1] = (*dptr)[size - 2];
		new_dptr[size] = 0;
		free(*dptr);
	}
	*dptr = new_dptr;
}
