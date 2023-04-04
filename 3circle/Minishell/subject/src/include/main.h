#ifndef MAIN_H
#define MAIN_H

#include "main.h"
#include "../../libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../builtins/builtins.h"
#include <termios.h>

#define REDIR_IN 1 //'<'
#define REDIR_OUT 2 //'>'
#define REDIR_APPEND 3 //'>>'
#define REDIR_HEREDOC 4 //'<<'
#define NULL_STATE 0
#define NOT_NULL_STATE 1

typedef struct s_redirect
{
	int type;
	char *file_name;
}	t_redirect;

typedef struct s_execution
{
	int is_terminated;
	char **exev_argv;
	t_redirect *redirect_ar;
}	t_execution;

void categorize_token(t_execution *exe_ptr, char **token_ar, char ***envp);
int is_valid_line(char *line);
void free_execution_ar(t_execution *execution_ar);
char	**make_token(char const *s);
char	**pipe_split(char const *s, char c);
void set_redirect_token(t_redirect *redirect_ptr, char *token);
t_execution *str_to_execution(char *line, char ***envp);
void print_all_execution(t_execution *execution_ar);
int execute(t_execution *execution, char ***envp, int **pipe_ar, int index);
char	*make_command_path(char *command, char **envp);
int execute_all(t_execution *execution_ar, char ***envp);
void signal_handler(int signum);
char *token_to_good_token(char *token, char ***envp);
void	input_handler(struct termios *term_ptr);
void	print_eof(void);
int change_exit_status(int status);
#endif