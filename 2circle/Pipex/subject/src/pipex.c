/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:45:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/02 13:23:19 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_do(int *pipe_fd, char **argv, char **envp)
{
	int		infile_fd;
	char	**command_with_path;

	infile_fd = open_file(*(argv + 1), O_RDONLY);
	if (dup2(pipe_fd[1], 1) == -1)
		exit_with_perror("dup2");
	if (dup2(infile_fd, 0) == -1)
		exit_with_perror("dup2");
	if (close(pipe_fd[0]) == -1)
		exit_with_perror("close");
	if (close(pipe_fd[1]) == -1)
		exit_with_perror("close");
	if (close(infile_fd) == -1)
		exit_with_perror("close");
	command_with_path = make_command_path(*(argv + 2), envp);
	if (execve(command_with_path[0], command_with_path, NULL) == -1)
		exit_with_perror(*(argv + 1));
}

void	parent_process_do(int *pipe_fd, char **argv, char **envp)
{
	int		outfile_fd;
	char	**command_with_path;

	outfile_fd = open_file(*(argv + 4), O_WRONLY | O_CREAT | O_TRUNC);
	if (dup2(pipe_fd[0], 0) == -1)
		exit_with_perror("dup2");
	if (dup2(outfile_fd, 1) == -1)
		exit_with_perror("dup2");
	if (close(pipe_fd[0]) == -1)
		exit_with_perror("close");
	if (close(pipe_fd[1]) == -1)
		exit_with_perror("close");
	if (close(outfile_fd) == -1)
		exit_with_perror("close");
	command_with_path = make_command_path(*(argv + 3), envp);
	if (execve(command_with_path[0], command_with_path, NULL) == -1)
		exit_with_perror(*(argv + 1));
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	fork_fd;

	if (argc != 5)
		exit_with_perror("argc is must 4");
	pipe(pipe_fd);
	fork_fd = fork();
	if (fork_fd == 0)
		child_process_do(pipe_fd, argv, envp);
	else
		parent_process_do(pipe_fd, argv, envp);
	exit(0);
}
