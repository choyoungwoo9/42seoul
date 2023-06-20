# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 09:24:41 by yuikim            #+#    #+#              #
#    Updated: 2023/06/14 16:14:42 by youngwch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
SRCS_DIR = ./src/
LIBFT_DIR = ./libft/

SRCS = builtins/cd.c builtins/check_builtins.c builtins/echo.c builtins/env.c\
		builtins/export.c builtins/minishell_utils.c\
		builtins/minishell_utils2.c builtins/exit.c\
		builtins/minishell_utils3.c builtins/pwd.c builtins/unset.c\
		execute/execute_all.c execute/execute_iterate.c execute/execute_util.c execute/execute_util2.c\
		execute/execute.c execute/here_doc.c execute/make_command_path.c\
		main/main.c\
		signal/signal_handler.c\
		parse/categorize_token.c parse/free_execution_ar.c parse/is_valid_line.c parse/make_token.c\
		parse/parsing_util.c parse/pipe_split.c parse/set_redirect_token.c\
		parse/str_to_execution.c parse/token_change_func.c parse/token_to_good_token.c\

%.o : %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = ${SRCS_PATH:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJS) $(COMFIILE_FLAGS) libft/libft.a -o $(NAME) -lreadline -L/Users/youngwch/.brew/opt/readline/lib


clean :
	make -C libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)
fclean : clean
	make -C libft fclean
	rm -rf $(NAME) $(OBJS) $(OBJS_BONUS)

re :
	make fclean
	make all
	
.PHONY:		all clean fclean bonus re