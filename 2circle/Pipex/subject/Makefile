CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/pipex.c src/pipex_make_command_path.c src/pipex_util.c

SRCS_BONUS = bonus/pipex_bonus.c bonus/pipex_heredoc_process_bonus.c \
		bonus/pipex_make_command_path_bonus.c bonus/pipex_recursive_pipe_bonus.c \
		bonus/pipex_util_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c 
	
NAME = pipex

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

ifdef HAVE_BONUS
	DETERMINED_OBJS = $(OBJS_BONUS)
else
	DETERMINED_OBJS = $(OBJS)
endif

all: make_libft ${NAME}

make_libft:
	make -C libft all

${NAME}: ${DETERMINED_OBJS}
	$(CC) $(CFLAGS) $^ libft/libft.a -o $@
clean:
	make -C libft clean
	rm -rf ${OBJS}
	rm -rf ${OBJS_BONUS}

fclean : clean
	make -C libft fclean
	rm -rf ${NAME}

re : fclean all

bonus :
	make HAVE_BONUS=1 all

.PHONY: bonus all clean fclean re