#ifndef MAIN_H
#define MAIN_H

#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
	char *cmd;
	t_redirect *redirect_ar;
	char **option_ar;
}	t_execution;

void categorize_token(t_execution *exe_ptr, char **token_ar);
int is_valid_line(char *line);
void free_execution_ar(t_execution *execution_ar);
char	**make_token(char const *s);
char	**pipe_split(char const *s, char c);
void set_redirect_token(t_redirect *redirect_ptr, char *token);
t_execution *str_to_execution(char *line);
void print_all_execution(t_execution *execution_ar);
#endif