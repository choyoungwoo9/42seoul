/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:58:13 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/22 10:04:17 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "mlx/mlx.h"
#include"get_next_line.h"
# include"libft/libft.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53

#define GROUND_PATH "textures/ground.xpm"
#define LAVA_PATH "textures/lava.xpm"
#define COIN_PATH "textures/coin.xpm"
#define COIN_SMALL_PATH "textures/coin_small(30).xpm"
#define DOOR_PATH "textures/door.xpm"
#define POCKETMON_FRONT_PATH "textures/pocketmon_front.xpm"
#define POCKETMON_BACK_PATH "textures/pocketmon_back.xpm"
#define POCKETMON_LEFT_PATH "textures/pocketmon_left.xpm"
#define POCKETMON_RIGHT_PATH "textures/pocketmon_right.xpm"

typedef struct s_mlx_data {
	void	*mlx;
	void	*win;
}	t_mlx_data;

typedef struct	s_game_data
{
	char	**maps;
	int	row;
	int column;
	int pocketmon_row;
	int pocketmon_column;
	int coin_count;
	int exit_row;
	int exit_column;
	int pocketmon_movement_count;
}	t_game_data;

typedef struct	s_all_data {
	t_mlx_data mlx_data;
	t_game_data game_data;
}	t_all_data;

#endif