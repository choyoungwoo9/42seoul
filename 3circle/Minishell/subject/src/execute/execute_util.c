/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:34:39 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 17:14:53 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

int	is_regular_file(char *exec_path)
{
	struct stat	buf;

	stat(exec_path, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFREG)
		return (1);
	return (0);
}

int	is_path(char *cmd_path)
{
	int	i;

	i = -1;
	while (cmd_path[++i])
	{
		if (cmd_path[i] == '/')
			return (1);
	}
	return (0);
}

int	is_dir(char *exec_path)
{
	struct stat	buf;

	stat(exec_path, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int	is_valid_path(char *exec_path)
{
	if (access(exec_path, X_OK | F_OK) == 0)
		return (1);
	return (0);
}

int	is_valid_permission(char *exec_path)
{
	struct stat	buf;

	stat(exec_path, &buf);
	if ((buf.st_mode & S_IXUSR) != 0)
		return (1);
	return (0);
}
