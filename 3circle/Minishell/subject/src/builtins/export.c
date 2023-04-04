/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:33:04 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/28 16:02:12 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export(char *arg, char ***envp)
{
	char	*arg_copy;
	char	*key;
	char	*value;
	char	*temp;

	if (!arg || !(*envp))
		return (1);
	if (ft_strchr(arg, '=') == NULL)
		return (1);
	arg_copy = ft_strdup(arg);
	temp = ft_strchr(arg_copy, '=');
	*temp = 0;
	key = arg_copy;
	value = temp + 1;
	set_env_value(envp, key, value);
	free(key);
	return (0);
}

int	export_no_option(char **envp)
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
