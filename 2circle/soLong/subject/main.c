/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:57:18 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/22 10:15:38 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "get_map.c"
#include "get_next_line.c"
#include "get_next_line_utils.c"
#include "make_mlx_instance_and_window.c"
#include "libft/ft_putnbr_fd.c"

void render_map(char **maps, void *mlx, void *win)
{
	int		img_width;
	int		img_height;
	void	*img;
	int i;
	int j;
	i = 0;
	while(*(maps + i))
	{
		j = 0;
		while(*(*(maps + i) + j))
		{
			img = mlx_xpm_file_to_image(mlx, GROUND_PATH, &img_width, &img_height);
			mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
			if(*(*(maps + i) + j) == '0')
			{
				img = mlx_xpm_file_to_image(mlx, GROUND_PATH, &img_width, &img_height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
			}
			else if(*(*(maps + i) + j) == '1')
			{
				img = mlx_xpm_file_to_image(mlx, LAVA_PATH, &img_width, &img_height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
			}
			else if(*(*(maps + i) + j) == 'c')
			{
				img = mlx_xpm_file_to_image(mlx, COIN_SMALL_PATH, &img_width, &img_height);
				mlx_put_image_to_window(mlx, win, img, j * 64 + 16, i * 64 + 16) ;
			}
			else if(*(*(maps + i) + j) == 'E')
			{
				img = mlx_xpm_file_to_image(mlx, DOOR_PATH, &img_width, &img_height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
			}
			
			else if(*(*(maps + i) + j) == 'P')
			{
				img = mlx_xpm_file_to_image(mlx, POCKETMON_FRONT_PATH, &img_width, &img_height);
				mlx_put_image_to_window(mlx, win, img, j * 64, i * 64);
				
			}
			j ++;
		}
		i ++;
	}
}

void set_game_data_from_map(t_game_data *game_data)
{
	char **map = game_data->maps;
	game_data->coin_count = 0;
	game_data->pocketmon_movement_count = 0;
	int i = 0;
	int j;
	while(*(map + i))
	{
		j = 0;
		while(*(*(map + i) + j))
		{
			if(*(*(map + i) + j) == 'P')
			{
				game_data->pocketmon_row = i;
				game_data->pocketmon_column = j;
			}
			if(*(*(map + i) + j) == 'E')
			{
				game_data->exit_row = i;
				game_data->exit_column = j;
			}
			if(*(*(map + i) + j) == 'c')
			{
				(game_data->coin_count) ++;
			}
			j ++;
		}
		i ++;
	}
}

int get_predicted_block(t_game_data *game_data, int keycode)
{
	int row;
	int column;

	row = game_data->pocketmon_row;
	column = game_data->pocketmon_column;
	if(keycode == KEY_A)
	{
		return (*(*(game_data->maps + row) + column - 1));
	}
	if(keycode == KEY_S)
	{
		return (*(*(game_data->maps + row + 1) + column));
	}
	if(keycode == KEY_D)
	{
		return (*(*(game_data->maps + row) + column + 1));
	}
	if(keycode == KEY_W)
	{
		return (*(*(game_data->maps + row - 1) + column));
	}
	return -1;
}

void move_pocketmon(t_game_data *game_data, int keycode)
{
	int row;
	int column;

	row = game_data->pocketmon_row;
	column = game_data->pocketmon_column;
	*(*(game_data->maps + row) + column) = '0';
	if(keycode == KEY_A)
	{
		game_data->pocketmon_column = game_data->pocketmon_column - 1;
		*(*(game_data->maps + row) + column - 1) = 'P';
	}
	if(keycode == KEY_S)
	{
		game_data->pocketmon_row = game_data->pocketmon_row + 1;
		*(*(game_data->maps + row + 1) + column) = 'P';
	}
	if(keycode == KEY_D)
	{
		game_data->pocketmon_column = game_data->pocketmon_column + 1;
		*(*(game_data->maps + row) + column + 1) = 'P';
	}
	if(keycode == KEY_W)
	{
		game_data->pocketmon_row = game_data->pocketmon_row - 1;
		*(*(game_data->maps + row - 1) + column) = 'P';
	}
}

void move_pocketmon_and_change_map(t_game_data *game_data, t_mlx_data *mlx_data,int keycode)
{
	char block = get_predicted_block(game_data, keycode);
	if(block == '0' || block == 'c')
	{
		if(block == 'c')
		{
			game_data->coin_count --;
		}
		move_pocketmon(game_data, keycode);
		game_data->pocketmon_movement_count ++;
		write(1, "current number of movements : ", 30);
		ft_putnbr_fd(game_data->pocketmon_movement_count, 0);
		write(1, "\n", 1);
	}
	if(block == 'E')
	{
		if(game_data->coin_count == 0)
		{
			mlx_destroy_window(mlx_data->mlx, mlx_data->win);
			game_data->pocketmon_movement_count ++;
			write(1, "current number of movements : ", 30);
			ft_putnbr_fd(game_data->pocketmon_movement_count, 0);
			write(1, "\n", 1);
			exit(0);
		}
	}
		
}

int key_hook(int keycode, t_all_data *all_data)
{
	t_mlx_data *mlx_data = &all_data->mlx_data;
	t_game_data *game_data = &all_data->game_data;
	if(keycode == KEY_ESC)
	 	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	if(keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || keycode == KEY_W)
	{
		move_pocketmon_and_change_map(game_data, mlx_data, keycode);
		
		render_map(game_data->maps, mlx_data->mlx, mlx_data->win);
	}
	return (0);
}

int main()
{
	t_all_data all_data;
	get_map(&all_data.game_data);
	make_mlx_instance_and_window(&all_data);
	render_map(all_data.game_data.maps, all_data.mlx_data.mlx, all_data.mlx_data.win);
	set_game_data_from_map(&all_data.game_data);
	mlx_key_hook(all_data.mlx_data.win, key_hook, &all_data);
	mlx_loop(all_data.mlx_data.mlx);
	
	
	return (0);
}
