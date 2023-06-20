/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:33:04 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/31 13:33:41 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static int	is_valid_env_str(char *str, int *ret)
{
	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		print_builtin_error(str);
		free(str);
		*ret = 1;
		return (0);
	}
	return (1);
}

static int	export_no_option(char **envp)
{
	char	**envp_copy;
	int		i;

	envp_copy = dptr_dup(envp);
	ft_sort_ascii(envp_copy, get_dptr_size(envp_copy));
	i = -1;
	while (envp_copy[++i])
		printf("declare -x %s\n", envp[i]);
	free_dptr(envp_copy, DEFAULT);
	return (0);
}

int	export(char **args, char ***envp)
{
	char	*arg_copy;
	char	*temp;
	int		ret;

	ret = 0;
	if (get_dptr_size(args) == 1)
		return (export_no_option(*envp));
	while (*(++args))
	{
		arg_copy = ft_strdup(*args);
		if (!is_valid_env_str(arg_copy, &ret))
			continue ;
		temp = ft_strchr(arg_copy, '=');
		if (temp != NULL)
		{
			*temp = 0;
			set_env_value(envp, arg_copy, temp + 1);
		}
		free(arg_copy);
	}
	return (ret);
}
