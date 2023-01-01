/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:46:14 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/01 16:03:39 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "get_next_line.h"

#define READ 0
#define WRITE 1

char	**make_command_path(char *command, char **envp);
void	exit_with_perror(char *message);
void	exit_with_message(char *message);
int		open_file(char *file_name, int option);
#endif