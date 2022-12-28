/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:45:45 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/28 21:42:21 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./libft/ft_strjoin.c"
#include "./libft/ft_strnstr.c"
#include "./libft/ft_strlen.c"
#include "./libft/ft_split.c"

#define SIZE 4

int main(int argc, char **argv, char **envp)
{
	int state;
	int pid = fork();
	int pipe_fd[2];
	int pipe_fd2[2];
	char buffer[10];
	pipe(pipe_fd);
	int fd = open("./file_a", O_RDONLY);
	if(pid == 0)
	{
		dup2(pipe_fd[1], 0);
		read(fd, buffer, 10);
	}
	else
	{
		//int pid2 = fork();
		//if(pid2 == 0)
		{
			char *arg[3];
			wait(&state);
			arg[0] = "/usr/bin/grep";
			arg[1] = "a";
			arg[2] = NULL;
			dup2(pipe_fd[0], 0);
			//dup2(pipe_fd2[1], 1);
			execve(arg[0], arg, NULL);	
		}
		// else
		// {
		// 	char *arg[3];
		// 	wait(&state);
		// 	arg[0] = "/usr/bin/wc";
		// 	arg[1] = "-w";
		// 	arg[2] = NULL;
		// 	dup2(pipe_fd2[0], 0);
		// 	execve(arg[0], arg, NULL);	
		// }
	}
}