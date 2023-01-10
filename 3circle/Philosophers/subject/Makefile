CC = cc
CFLAGS = -Wall -Wextra -Werror#-g3 -fsanitize=thread -Wall -Wextra -Werror
SRCS = src/philosopher.c src/philosopher_set_dinner.c \
		src/philosopher_start_dinner.c src/philosopher_start_dinner_do.c \
		src/philosopher_observe_dinner.c src/philosopher_util.c

# SRCS_BONUS = bonus/pipex_bonus.c bonus/pipex_heredoc_process_bonus.c \
# 		bonus/pipex_make_command_path_bonus.c bonus/pipex_recursive_pipe_bonus.c \
# 		bonus/pipex_util_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c 
	
NAME = philosopher

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

ifdef HAVE_BONUS
	DETERMINED_OBJS = $(OBJS_BONUS)
else
	DETERMINED_OBJS = $(OBJS)
endif

all: ${NAME}

${NAME}: ${DETERMINED_OBJS}
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

# bonus :
# 	make HAVE_BONUS=1 all

.PHONY: bonus all clean fclean re