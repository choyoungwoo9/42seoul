/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:45:45 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/28 20:18:00 by youngwch         ###   ########.fr       */
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



int main(int argc, char **argv, char **envp)
{
	// if(argc != 2)
	// {
	// 	printf("arg need 2\n");
	// 	return 0;
	// }
	// int i = 0;
	// while(*(envp + i))
	// {
	// 	if(ft_strnstr(*(envp + i), "PATH=", ft_strlen(*(envp + i))))
	// 		break;
	// 	i ++;
	// }
	// char **tmp_ar = ft_split(*(envp + i), '=');
	// char **s_ar = ft_split(*(tmp_ar + 1), ':');
	// i = 0;
	// while(*(s_ar + i))
	// {
	// 	char *tmp;
	// 	tmp = ft_strjoin(*(s_ar + i), "/");
	// 	tmp = ft_strjoin(tmp, argv[1]);
	// 	printf("%s\n", tmp);
	// 	char *ss[2] = {tmp, NULL};
	// 	if(execve(tmp, ss, NULL))
	// 		printf("i : %d\n", i);
	// 	i ++;
	// }
	// //경로 배열 만듬

	// char buffer[8];
	// int fd0 = open("./file_a", O_RDONLY);
	// read(fd0, buffer, 8);
	

	// int fd1 = open("./file_b", O_WRONLY);
	// write(1, "abcde\n", 6);
	// dup2(fd1, STDOUT_FILENO);
	// write(1, "abcde\n", 6);
	// write(fd1, "abcdeef\n", 6);
	
	// int status;
	// int pid, child_pid;
	
	// pid = fork();
	// if(pid != 0)
	// {
	// 	printf("fork리턴값 : %d\n", pid);
	// 	//child_pid = wait(&status);
	// 	child_pid = waitpid(pid, &status, WNOHANG);
	// 	printf("자식 pid : %d, status : %d\n", child_pid, status);
	// 	child_pid = waitpid(pid, &status, 0);
	// 	printf("자식 pid : %d, status : %d\n", child_pid, status);
	// }
	// else
	// {
	// 	printf("자식 1\n");
	// 	printf("자식 2\n");
	// 	printf("자식 3\n");
	// 	exit(5);
	// }
	
	
}