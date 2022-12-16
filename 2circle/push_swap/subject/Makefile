CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c greedy_alog.c greedy_counter.c \
		operation1.c operation1.c operation1.c operation1.c \
		primary_logic.c stack_operation.c util.c util2.c

NAME = push_swap

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
