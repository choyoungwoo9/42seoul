/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:46:14 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/08 10:09:04 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "get_next_line_bonus.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define READ 0
# define WRITE 1

typedef struct s_argv_and_envp {
	char	**argv;
	char	**envp;
}	t_argv_and_envp;

char	**make_command_path(char *command, char **envp);
void	exit_with_perror(char *message);
int		open_file(char *file_name, int option);
void	pipex_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);
void	recursive_pipe(int *pipe_after, char **argv, int index, char **envp);
void	heredoc_process(char **argv, char **envp);
#endif