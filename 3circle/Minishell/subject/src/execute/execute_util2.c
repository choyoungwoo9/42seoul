/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:12:00 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 14:12:17 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	exit_with_perror(char *message)
{
	perror(message);
	exit(1);
}

int	open_file(char *file_name, int option)
{
	char	*file_path;
	int		fd;

	if (*file_name == '/')
		file_path = ft_strjoin("", file_name);
	else
		file_path = ft_strjoin("./", file_name);
	fd = open(file_path, option, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit_with_perror(file_name);
	free(file_path);
	return (fd);
}
