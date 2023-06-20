/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:35:26 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 10:21:55 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

static void	free_pipe(int **pipe_ar)
{
	int	i;

	i = -1;
	while (pipe_ar[++i])
		free(pipe_ar[i]);
	free(pipe_ar);
}

static void	change_exit_status(int status)
{
	int	my_signal;

	if (WIFEXITED(status))
	{
		g_exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		my_signal = WTERMSIG(status);
		g_exit_code = my_signal + 128;
	}
	else if (WIFSTOPPED(status))
	{
		my_signal = WSTOPSIG(status);
		g_exit_code = my_signal + 128;
	}
	else
		g_exit_code = status;
}

static int	**malloc_pipe(t_execution *execution_ar)
{
	int	**pipe_ar;
	int	p_count;
	int	i;

	p_count = 0;
	while (execution_ar[p_count].is_terminated != NULL_STATE)
		p_count ++;
	if (p_count)
	{
		pipe_ar = malloc(sizeof(int *) * (p_count));
		pipe_ar[p_count - 1] = NULL;
	}
	else
	{
		pipe_ar = malloc(sizeof(int *) * 1);
		pipe_ar[0] = NULL;
	}
	i = -1;
	while (++i < p_count - 1)
	{
		pipe_ar[i] = malloc(sizeof(int) * 2);
		pipe(pipe_ar[i]);
	}
	return (pipe_ar);
}

void	execute_all(t_execution *execution_ar, char ***envp)
{
	int	**pipe_ar;
	int	exit_status;

	pipe_ar = malloc_pipe(execution_ar);
	exit_status = execute_iterate(execution_ar, envp, pipe_ar);
	change_exit_status(exit_status);
	free_pipe(pipe_ar);
	return ;
}
