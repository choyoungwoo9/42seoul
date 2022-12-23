# rm -f a.out
# cc -Wall -Wextra -Werror -L./mlx -lmlx -framework OpenGL -framework AppKit -o so_long so_long.c get_next_line.c get_next_line_utils.c so_long_get_map.c so_long_make_mlx_instance_and_window.c so_long_render_map.c so_long_set_game_data_from_map.c so_long_hook_event.c so_long_check_valid_map.c so_long_check_valid_component.c so_long_check_valid_map_path.c so_long_check_valid.c so_long_util.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_strdup.c libft/ft_split.c libft/ft_putchar_fd.c

# cc -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit main.c
# gcc *.c -I. -Lmlx -lmlx -framework OpenGL -framework Appkit
#-frameword OpenGL -framework AppKit -lz
ARG="not_valid"
./so_long $ARG
ARG="invalid_not_rectangular_map.ber"
./so_long $ARG
ARG="invalid_empty_map.ber"	
./so_long $ARG
ARG="invalid_so_small_map.ber"
./so_long $ARG
ARG="invalid_not_surrouned_wall_map.ber"
./so_long $ARG
ARG="invalid_another_component_map.ber"
./so_long $ARG
ARG="invalid_not_one_door_map.ber"
./so_long $ARG
ARG="invalid_not_one_pocketmon_map.ber.ber"
./so_long $ARG
ARG="invalid_zero_coin_map.ber"
./so_long $ARG
ARG="invalid_path_map.ber"
./so_long $ARG
ARG="valid_map.ber"
./so_long $ARG
# ARG="valid_map2.ber"
# ./so_long $ARG