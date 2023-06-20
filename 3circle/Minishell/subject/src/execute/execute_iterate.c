/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_iterate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:35:29 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 10:23:54 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

static int	is_main_process_execute(t_execution *execution_ar)
{
	if (!execution_ar->exev_argv)
		return (0);
	if (is_same_str(execution_ar->exev_argv[0], "cd"))
		return (1);
	if (is_same_str(execution_ar->exev_argv[0], "env"))
		return (1);
	if (is_same_str(execution_ar->exev_argv[0], "export"))
		return (1);
	if (is_same_str(execution_ar->exev_argv[0], "unset"))
		return (1);
	if (is_same_str(execution_ar->exev_argv[0], "pwd"))
		return (1);
	if (is_same_str(execution_ar->exev_argv[0], "exit"))
		return (1);
	return (0);
}

static int	wait_child(t_execution *execution_ar, int pid)
{
	int	exit_status;
	int	status;
	int	child_id;

	while (1)
	{
		g_exit_code = -1;
		child_id = wait(&status);
		if (child_id <= 0)
		{
			remove_temp_file(execution_ar);
			break ;
		}
		if (child_id == pid)
			exit_status = status;
	}
	return (exit_status);
}

int	execute_iterate(t_execution *execution_ar, char ***envp, int **pipe_ar)
{
	int	i;
	int	p_count;
	int	pid;

	i = -1;
	p_count = 0;
	while (execution_ar[p_count].is_terminated != NULL_STATE)
		p_count ++;
	if (p_count == 1 && is_main_process_execute(execution_ar))
		return (execute(execution_ar, envp, pipe_ar, 0));
	while (++i < p_count)
	{
		pid = fork();
		if (pid == 0)
			exit(execute(execution_ar + i, envp, pipe_ar, i));
		else
		{
			if (i != 0)
				close(pipe_ar[i - 1][0]);
			if (pipe_ar[i] != NULL)
				close(pipe_ar[i][1]);
		}
	}
	return (wait_child(execution_ar, pid));
}
