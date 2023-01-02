/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_recursive_pipe_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:15:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/02 10:54:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parent_do(t_argv_and_envp tmp_struct, int index,
	int *pipe_after, int *pipe_fd)
{
	char	**tmp;
	int		input_fd;
	int		output_fd;
	char	**argv;
	char	**envp;

	argv = tmp_struct.argv;
	envp = tmp_struct.envp;
	tmp = make_command_path(*(argv + index), envp);
	if (index == 2)
		input_fd = open_file(*(argv + index - 1), O_RDONLY);
	else
		input_fd = pipe_fd[READ];
	if (!*(argv + index + 2))
		output_fd = open_file(*(argv + index + 1), O_WRONLY | O_CREAT | O_TRUNC);
	else
		output_fd = pipe_after[WRITE];
	if (dup2(input_fd, 0) == -1)
		exit_with_perror("dup2");
	if (dup2(output_fd, 1) == -1)
		exit_with_perror("dup2");
	if (close(pipe_fd[WRITE]) == -1)
		exit_with_perror("close");
	if (execve(*(tmp + 0), tmp, envp) == -1)
		exit_with_message("cmd");
}

void	recursive_pipe(int *pipe_after, char **argv, int index, char **envp)
{
	int				pipe_fd[2];
	pid_t			pid;
	t_argv_and_envp	tmp_struct;

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
		tmp_struct.argv = argv;
		tmp_struct.envp = envp;
		parent_do(tmp_struct, index, pipe_after, pipe_fd);
	}
}
