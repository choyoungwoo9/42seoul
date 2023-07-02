CC = cc
CFLAGS = -fsanitize=thread -Wall -Wextra -Werror
SRCS = philosopher.c philosopher_make_table.c philosopher_end_check.c\
		philosopher_thread_init.c philosopher_util.c philosopher_primary_util.c\
		philosopher_do.c
	
NAME = philo

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

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

.PHONY: all clean fclean re
