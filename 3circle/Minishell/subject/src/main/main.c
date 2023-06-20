/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:59:58 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/02 11:35:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	g_exit_code = 0;

static void	terminal_routine(char *line,
		char ***envp, t_execution *execution_ar)
{
	if (!*line)
	{
		free(line);
		return ;
	}
	add_history(line);
	if (!is_valid_line(line))
	{
		printf("syntax error\n");
		g_exit_code = 258;
		free(line);
		return ;
	}
	execution_ar = str_to_execution(line, envp);
	free(line);
	line = NULL;
	if (execution_ar)
	{
		execute_all(execution_ar, envp);
		free_execution_ar(execution_ar);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_execution		*execution_ar;
	struct termios	term;

	envp = dptr_dup(envp);
	input_handler(&term);
	handle_signal();
	execution_ar = NULL;
	if (argc >= 2 && *(argv + 1))
	{
		ft_putstr_fd("invalid option\n", 1);
		return (127);
	}
	while (1)
	{
		line = readline("bash $ ");
		if (line)
			terminal_routine(line, &envp, execution_ar);
		else
		{
			print_eof();
			exit(0);
		}
	}
	return (0);
}
