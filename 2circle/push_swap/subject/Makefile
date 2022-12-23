CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c greedy_algo.c greedy_counter.c sort_few_stack.c\
		operation1.c operation2.c operation3.c operation4.c \
		primary_logic.c stack_operation.c util.c util2.c

NAME = push_swap

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: make_libft ${NAME}

make_libft:
	make -C libft all

${NAME}: ${OBJS}
	cp libft/libft.a libft.a
	$(CC) $(CFLAGS) $^ libft.a -o $@ 
clean:
	make -C libft clean
	rm -rf libft.a
	rm -rf ${OBJS}

fclean : clean
	make -C libft fclean
	rm -rf ${NAME}

re : fclean all