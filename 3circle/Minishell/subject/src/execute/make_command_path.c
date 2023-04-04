/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:45:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/28 11:39:13 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_string_array(char **str_array)
{
	int	i;

	i = -1;
	while (*(str_array + ++i))
		free(*(str_array + i));
	free(str_array);
}

static char	*select_exec_path(char *command, char **env_path_array)
{
	char	*exec_path;
	char	*tmp_str;
	int		i;

	i = -1;
	while (*(env_path_array + ++i))
	{
		tmp_str = ft_strjoin("/", command);
		exec_path = ft_strjoin(env_path_array[i], tmp_str);
		free(tmp_str);
		if (access(exec_path, F_OK) == 0)
			break ;
		free(exec_path);
		if (env_path_array[i+1] == NULL)
			exec_path = NULL;
	}
	free_string_array(env_path_array);
	return (exec_path);
}

static char	**make_exec_path(char **envp)
{
	char	*env_path;
	char	*env_tem_path;
	char	**split_array;
	int		i;

	i = -1;
	while (*(envp + ++i))
	{
		if (ft_strnstr(*(envp + i), "PATH=", ft_strlen(*(envp + i))))
			env_tem_path = ft_strnstr(*(envp + i), "PATH=",
					ft_strlen(*(envp + i)));
	}
	split_array = ft_split(env_tem_path, '=');
	env_path = ft_strdup(*(split_array + 1));
	free_string_array(split_array);
	split_array = ft_split(env_path, ':');
	free(env_path);
	return (split_array);
}

char	*make_command_path(char *command, char **envp)
{
	char	*command_path;
	char	**env_path_array;

	env_path_array = make_exec_path(envp);
	command_path = select_exec_path(command, env_path_array);
	return (command_path);
}
