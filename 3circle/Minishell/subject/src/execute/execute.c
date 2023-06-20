/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:36:08 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/02 12:01:02 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

static void	set_fd(t_redirect *redirect, int *i_fd_ref, int *o_fd_ref)
{
	int	i;
	int	option;

	i = -1;
	while (redirect[++i].type != NULL_STATE)
	{
		if (redirect[i].type == REDIR_IN || redirect[i].type == REDIR_HEREDOC)
		{
			if (redirect[i].type == REDIR_IN)
				*i_fd_ref = open_file(redirect[i].file_name, O_RDONLY);
			if (redirect[i].type == REDIR_HEREDOC)
				*i_fd_ref = open_here_doc(redirect[i].file_name,
						&(redirect[i].temp_file));
		}
		else if (redirect[i].type == REDIR_OUT
			|| redirect[i].type == REDIR_APPEND)
		{
			if (redirect[i].type == REDIR_OUT)
			option = O_CREAT | O_WRONLY | O_TRUNC;
			else if (redirect[i].type == REDIR_APPEND)
				option = O_CREAT | O_APPEND | O_WRONLY;
			*o_fd_ref = open_file(redirect[i].file_name, option);
		}
	}
}

static void	make_default_iofd(int *input_fd,
	int *output_fd, int index, int **pipe_ar)
{
	if (index == 0)
		*input_fd = 0;
	else
	{
		*input_fd = pipe_ar[index - 1][0];
		close(pipe_ar[index - 1][1]);
	}
	if (pipe_ar[index] == NULL)
		*output_fd = 1;
	else
	{
		*output_fd = pipe_ar[index][1];
		close(pipe_ar[index][0]);
	}	
}

static void	check_invalid_cmd(char *cmd_path)
{
	if (!is_path(cmd_path))
	{
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (is_dir(cmd_path))
	{
		g_exit_code = 126;
		return ;
	}
	if (is_valid_permission(cmd_path))
	{
		g_exit_code = 1;
		return ;
	}
	return ;
}

int	execute(t_execution *execution, char ***envp, int **pipe_ar, int index)
{
	int		input_fd;
	int		output_fd;
	char	*cmd_path;
	int		builtin_flag;

	make_default_iofd(&input_fd, &output_fd, index, pipe_ar);
	set_fd(execution->redirect_ar, &input_fd, &output_fd);
	dup2(input_fd, 0);
	dup2(output_fd, 1);
	if (!execution->exev_argv[0])
		exit(0);
	builtin_flag = check_builtins(execution->exev_argv, envp);
	if (builtin_flag != -1)
		return (builtin_flag);
	if (!is_path(execution->exev_argv[0]))
		cmd_path = make_command_path(execution->exev_argv[0], *envp);
	else
	{
		cmd_path = execution->exev_argv[0];
	}
	check_invalid_cmd(cmd_path);
	if (execve(cmd_path, execution->exev_argv, *envp) == -1)
		exit_with_perror(cmd_path);
	return (g_exit_code);
}
