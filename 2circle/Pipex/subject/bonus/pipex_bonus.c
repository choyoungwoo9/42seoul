/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:03:08 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/01 19:56:35 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_strjoin.c"
#include "../libft/ft_strnstr.c"
#include "../libft/ft_split.c"
#include "../libft/ft_strlen.c"
#include "../libft/ft_strdup.c"
#include "../libft/ft_strncmp.c"
#include "../libft/ft_substr.c"
#include "../libft/ft_putstr_fd.c"
#include "pipex_bonus.h"

#include "pipex_make_command_path_bonus.c"
#include "pipex_util_bonus.c"
#include "pipex_recursive_pipe.c"
#include "get_next_line.c"
#include "get_next_line_utils.c"

//1 heredoc 2 LIMIT 3 cmd1 4 cmd2 5 file

int main(int argc, char** argv, char **envp)
{
	if(argc < 5)
		exit_with_message("few arg\n");
	if(!ft_strncmp("here_doc", *(argv + 1), ft_strlen("here_doc")))
	{
		if(argc != 6)
			exit_with_message("heredoc_must_have_5_arg\n");
		char *all_str;
		all_str = ft_strdup("");
		while(1)
		{
			ft_putstr_fd("> ", 1);
			char *str = get_next_line(0);
			if(!str) //ctrl d 로 나가는 경우
				break;
			//else if(check_limiter(str)) //limit로 끝냈을 때
			// {
			// 	free(str);
			// 	break;
			// }
			char *tmp = all_str;
			all_str = ft_strjoin(all_str, str);
			free(tmp);
		}
		int pipe_fd2[2];
		pipe(pipe_fd2);
		pid_t fork_pid = fork();
		if(fork_pid == 0)
		{
			int pipe_fd[2];
			pipe(pipe_fd);
			dup2(pipe_fd[0], 0);
			dup2(pipe_fd[1], 1);
			write(1, all_str, ft_strlen(all_str));
			close(pipe_fd[1]);
			dup2(pipe_fd2[1], 1);
			char **tmp = make_command_path(*(argv + 3), envp);
			execve(tmp[0], tmp, NULL);	
		}
		else
		{
			dup2(pipe_fd2[0], 0);	
			close(pipe_fd2[1]);		
			int out_fd = open_file(*(argv + 5),O_WRONLY | O_CREAT | O_APPEND);
			dup2(out_fd, 1);
			close(out_fd);
			char **tmp = make_command_path(*(argv + 4), envp);
			execve(tmp[0], tmp, NULL);
		}
	}
	else
		recursive_pipe(NULL, argv, argc - 2, envp);
}


//입력으로 닫는 파이프 dup2후 출력파이프를 닫아야 eof주는듯(열려있으면 eof를 안줘서 계속 받음)
