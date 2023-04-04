/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_process_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:38:21 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/02 13:03:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_do(int *pipe_fd, char **argv, char **envp, char *all_str)
{
	int		pipe_tmp_fd[2];
	char	**tmp;

	if (pipe(pipe_tmp_fd) == -1)
		exit_with_perror("pipe");
	if (dup2(pipe_tmp_fd[0], 0) == -1)
		exit_with_perror("dup2");
	if (dup2(pipe_tmp_fd[1], 1) == -1)
		exit_with_perror("dup2");
	write(1, all_str, ft_strlen(all_str));
	if (close(pipe_tmp_fd[1]) == -1)
		exit_with_perror("close");
	if (dup2(pipe_fd[1], 1) == -1)
		exit_with_perror("dup2");
	tmp = make_command_path(*(argv + 3), envp);
	if (execve(tmp[0], tmp, envp) == -1)
		exit_with_perror("execve");
}

static void	parent_do(int *pipe_fd, char **argv, char **envp)
{
	int		out_fd;
	char	**tmp;

	if (dup2(pipe_fd[0], 0) == -1)
		exit_with_perror("dup2");
	if (close(pipe_fd[1]) == -1)
		exit_with_perror("close");
	out_fd = open_file(*(argv + 5), O_WRONLY | O_CREAT | O_APPEND);
	if (dup2(out_fd, 1) == -1)
		exit_with_perror("dup2");
	tmp = make_command_path(*(argv + 4), envp);
	if (execve(tmp[0], tmp, envp) == -1)
		exit_with_perror("execve");
}

static int	null_or_limiter(char *str, char *limiter)
{
	if (!str)
		return (1);
	if ((ft_strlen(str) - 1) != ft_strlen(limiter))
		return (0);
	if (ft_strncmp(str, limiter, ft_strlen(limiter)))
		return (0);
	free(str);
	return (1);
}

static void	transfer_with_pipe_and_exec(char **argv, char **envp, char *data)
{
	int		pipe_fd[2];
	pid_t	fork_pid;

	if (pipe(pipe_fd) == -1)
		exit_with_perror("pipe");
	fork_pid = fork();
	if (fork_pid == -1)
		exit_with_perror("fork");
	if (fork_pid == 0)
		child_do(pipe_fd, argv, envp, data);
	else
		parent_do(pipe_fd, argv, envp);
}

void	heredoc_process(char **argv, char **envp)
{
	char	*all_str;
	char	*str;
	char	*tmp;

	all_str = ft_strdup("");
	while (1)
	{
		pipex_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (null_or_limiter(str, *(argv + 2)))
			break ;
		tmp = all_str;
		all_str = ft_strjoin(all_str, str);
		free(tmp);
	}
	transfer_with_pipe_and_exec(argv, envp, all_str);
}
