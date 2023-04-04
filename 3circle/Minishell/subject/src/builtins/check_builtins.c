/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:09:00 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/28 20:02:34 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int is_same_str(char *str1, char *str2)
{
	if(!str1 || !str2)
		return 0;
	if(ft_strlen(str1) != ft_strlen(str2))
		return 0;
	if(ft_strncmp(str1, str2, ft_strlen(str1)) != 0)
		return 0;
	return 1;
}

static int	execute_arg_size_zero(char **args, char ***envp)
{
	if (is_same_str(args[0], "cd"))
		return (cd("~", envp));
	if (is_same_str(args[0], "env"))
		return (env(*envp));
	if (is_same_str(args[0], "exit"))
		ms_exit(args, EXIT_SUCCESS);
	if (is_same_str(args[0], "export"))
		return (export_no_option(*envp));
	if (is_same_str(args[0], "unset"))
		return (0);
	return (-1);
}

int	check_builtins(char **args, char ***envp)
{
	if (!args)
		return (-1);
	if (get_dptr_size(args) == 0)
		return (0);
	if (is_same_str(args[0], "echo"))
		return (echo(args));
	if (is_same_str(args[0], "pwd"))
		return (pwd());
	if (get_dptr_size(args) == 1)
		return (execute_arg_size_zero(args, envp));
	if (get_dptr_size(args) == 2)
	{
		if (is_same_str(args[0], "cd"))
			return (cd(args[1], envp));
		if (is_same_str(args[0], "export"))
			return (export(args[1], envp));
		if (is_same_str(args[0], "unset"))
			return (unset(args[1], *envp));
		if (is_same_str(args[0], "exit"))
			ms_exit(args, ft_atoi(args[1]) % 256);
	}
	return (-1);
}
