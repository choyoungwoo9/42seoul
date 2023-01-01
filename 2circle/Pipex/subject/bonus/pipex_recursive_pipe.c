/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_recursive_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:15:45 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/01 15:16:31 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void recursive_pipe(int *pipe_after, char **argv, int index, char **envp)
{
	char **tmp;
	int pipe_fd[2];
	int input_fd;
	int output_fd;
	pid_t pid;
	
	pipe(pipe_fd);
	pid = fork();

	if(pid == 0)
	{
		if(index > 2)
			recursive_pipe(pipe_fd, argv, --index, envp);
	}
	else
	{
		tmp = make_command_path(*(argv + index), envp);
		if(index == 2)
			input_fd = open_file(*(argv + index - 1), O_RDONLY);
		else
			input_fd = pipe_fd[READ];
		if(!*(argv + index + 2))
			output_fd = open_file(*(argv + index + 1), O_WRONLY | O_CREAT | O_TRUNC);
		else
			output_fd = pipe_after[WRITE];
		if(dup2(input_fd, 0) == -1)
			exit_with_perror("dup2");
		if(dup2(output_fd, 1) == -1)
			exit_with_perror("dup2");
		if(close(pipe_fd[WRITE]) == -1)
			exit_with_perror("close");
		if(execve(*(tmp + 0), tmp, envp) == -1)
			exit_with_message("cmd");
	}
}