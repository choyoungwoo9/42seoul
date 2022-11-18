CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c

NAME = libftprintf.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	make -C libft all
	make -C libft bonus
	ar r $@ $^ libft/libft.a

clean:
	make -C libft clean
	rm -rf ${OBJS}

fclean : clean
	make -C libft fclean
	rm -rf ${NAME}

re : fclean all
	make -C libft re