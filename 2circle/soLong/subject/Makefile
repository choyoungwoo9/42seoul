CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = so_long.c so_long_make_mlx_instance_and_window.c so_long_render_map.c \
		so_long_set_game_data_from_map.c so_long_hook_event.c \
		so_long_check_valid_map.c so_long_check_valid_component.c \
		so_long_check_valid_map_path.c so_long_check_valid.c so_long_util.c \
		get_next_line.c get_next_line_utils.c so_long_get_map.c \

NAME = so_long

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

all: make_libft ${NAME}

make_libft:
	make -C libft all
	make -C mlx all

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) -L./mlx -lmlx -framework OpenGL -framework AppKit $^ \
	./libft/libft.a ./mlx/libmlx.a -o $@ 
clean:
	make -C libft clean
	make -C mlx clean
	rm -rf ${OBJS}

fclean : clean
	make -C libft fclean
	rm -rf ${NAME}

re : fclean all