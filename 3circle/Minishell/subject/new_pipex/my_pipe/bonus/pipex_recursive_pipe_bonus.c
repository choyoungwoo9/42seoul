/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_recursive_pipe_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:15:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/26 17:58:56 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parent_do(t_argv_and_envp arg_or_env, int index,
	int *pipe_after, int *pipe_fd)
{
	char	**tmp;
	int		input_fd;
	int		output_fd;

	tmp = make_command_path(*(arg_or_env.argv + index), arg_or_env.envp);
	if (index == 2)
		input_fd = open_file(*(arg_or_env.argv + index - 1), O_RDONLY);
	else
		input_fd = pipe_fd[READ];
	if (!*(arg_or_env.argv + index + 2))
		output_fd = open_file(*(arg_or_env.argv + index + 1),
				O_WRONLY | O_CREAT | O_TRUNC);
	else
		output_fd = pipe_after[WRITE];
	if (dup2(input_fd, 0) == -1)
		exit_with_perror("dup2");
	if (dup2(output_fd, 1) == -1)
		exit_with_perror("dup2");
	if (close(pipe_fd[WRITE]) == -1)
		exit_with_perror("close");
	if (execve(*(tmp + 0), tmp, arg_or_env.envp) == -1)
		exit_with_perror("cmd");
}

void	recursive_pipe(int *pipe_after, char **argv, int index, char **envp)
{
	int				pipe_fd[2];
	pid_t			pid;
	t_argv_and_envp	arg_or_env;

	if (pipe(pipe_fd) == -1)
		exit_with_perror("pipe");
	pid = fork();
	if (pid < 0)
		exit_with_perror("fork");
	if (pid == 0)
	{
		if (index > 2)
			recursive_pipe(pipe_fd, argv, --index, envp);
	}
	else
	{
		arg_or_env.argv = argv;
		arg_or_env.envp = envp;
		parent_do(arg_or_env, index, pipe_after, pipe_fd);
	}
}
