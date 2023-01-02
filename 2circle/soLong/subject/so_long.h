/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:13 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/25 10:50:12 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include"mlx/mlx.h"
# include"get_next_line.h"
# include"libft/libft.h"
# include<stdlib.h>
# include<fcntl.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define EVENT_ON_DESTROY 17
# define GROUND_PATH "textures/ground.xpm"
# define LAVA_PATH "textures/lava.xpm"
# define COIN_SMALL_PATH "textures/coin_small(30).xpm"
# define DOOR_PATH "textures/door.xpm"
# define POCKETMON_FRONT_PATH "textures/pocketmon_front.xpm"

typedef struct s_mlx_data {
	void	*mlx;
	void	*win;
}	t_mlx_data;

typedef struct s_game_data
{
	char	**maps;
	int		row;
	int		column;
	int		pocketmon_row;
	int		pocketmon_column;
	int		coin_count;
	int		exit_row;
	int		exit_column;
	int		pocketmon_movement_count;
}	t_game_data;

typedef struct s_all_data {
	t_mlx_data	mlx_data;
	t_game_data	game_data;
}	t_all_data;
void	get_map(t_game_data *game_data, char *arg);
int		event_key_hook(int keycode, t_all_data *all_data);
int		event_closed_by_red_cross(int keycode, t_mlx_data *mlx_data);
void	make_mlx_instance_and_window(t_all_data *all_data);
void	render_map(char **maps, t_mlx_data *mlx_data);
void	set_game_data_from_map(t_game_data *game_data);
int		count_all_coin(char **maps);
void	get_pocketmon_row_column(char **maps,
			int *pocketmon_row, int *pocketmon_column);
char	**copy_map(char **maps);
void	free_map(char **map);
void	check_valid_map(t_game_data game_data);
int		is_minimal_map_size(char **maps);
int		is_rectangular_map(char **maps);
int		is_map_surrounded_wall(char **maps);
int		is_have_valid_path(char **maps);
int		is_one_pocketmon(char **maps);
int		is_one_door(char **maps);
int		is_have_at_least_one_coin(char **maps);
int		is_have_another_component(char **maps);
void	print_error_exit(char *message);
#endif