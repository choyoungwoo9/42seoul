/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:08:18 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 14:07:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "builtins.h"
# include "../../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/errno.h>

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4
# define NULL_STATE 0
# define NOT_NULL_STATE 1

typedef struct s_redirect
{
	int		type;
	char	*file_name;
	char	*temp_file;
}	t_redirect;

typedef struct s_execution
{
	int			is_terminated;
	char		**exev_argv;
	t_redirect	*redirect_ar;
}	t_execution;

void		execute_all(t_execution *execution_ar, char ***envp);
int			execute_iterate(t_execution *execution_ar,
				char ***envp, int **pipe_ar);
int			execute(t_execution *execution,
				char ***envp, int **pipe_ar, int index);
void		free_execution_ar(t_execution *execution_ar);
char		*make_command_path(char *command, char **envp);
int			open_here_doc(char *limiter, char **temp_file);
void		remove_temp_file(t_execution *execution);
void		print_eof(void);
char		*get_ptr_str(int *ptr);
void		exit_with_perror(char *message);
int			open_file(char *file_name, int option);
int			is_path(char *cmd_path);
int			is_dir(char *exec_path);
int			is_regular_file(char *exec_path);
t_execution	*str_to_execution(char *line, char ***envp);
void		categorize_token(t_execution *exe_ptr,
				char **token_ar, char ***envp);
int			is_valid_line(char *line);
char		**make_token(char *s);
char		**pipe_split(char *s, char c);
void		set_redirect_token(t_redirect *redirect_ptr, char *token);
char		*token_to_good_token(char *token, char ***envp);
void		input_handler(struct termios *term_ptr);
int			get_str_length_by_limiter(char *str, int index, char limiter);
char		*triple_join(char *str1, char *str2, char *str3);
char		*make_exit_code(char *str, int index);
int			is_env_var(char *str);
int			get_env_var_length(char *str);
char		*change_double_quote(char *token,
				int *start, int end, char ***envp);
char		*change_single_quote(char *token, int start, int end);
char		*change_env_var(char *token, int start, int end, char ***envp);
void		handle_signal(void);
void		signal_handler(int signum);
int			is_valid_permission(char *exec_path);
int			is_valid_path(char *exec_path);
#endif