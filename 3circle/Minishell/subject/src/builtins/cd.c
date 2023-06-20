/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:16:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 14:10:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static int	change_pwd_env(char *new_path, char ***envp)
{
	char	*buffer;

	if (chdir(new_path) == -1)
	{
		show_error(new_path);
		return (1);
	}
	buffer = get_pwd();
	set_env_value(envp, "PWD", buffer);
	free(buffer);
	return (0);
}

int	cd(char *path, char ***envp)
{
	char	*buffer;

	if (!path)
		return (change_pwd_env(get_env_value(*envp, "HOME"), envp));
	buffer = get_pwd();
	set_env_value(envp, "OLDPWD", buffer);
	free(buffer);
	return (change_pwd_env(path, envp));
}
