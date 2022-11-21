CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c printf_util.c printf_util2.c

NAME = libftprintf.a

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: make_libft ${NAME}

make_libft:
	make -C libft all
	make -C libft bonus
	

${NAME}: ${OBJS}
	cp libft/libft.a ${NAME}
	ar r $@ $^

clean:
	make -C libft clean
	rm -rf ${OBJS}

fclean : clean
	make -C libft fclean
	rm -rf ${NAME}

re : fclean all
	make -C libft re
	make -C libft bonus

bonus :