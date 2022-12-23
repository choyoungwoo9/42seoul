/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_hook_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:28:24 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 17:50:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_predicted_block(t_game_data *game_data, int keycode)
{
	if (keycode == KEY_A)
		return (*(*(game_data->maps + game_data->pocketmon_row)
				+ game_data->pocketmon_column - 1));
	else if (keycode == KEY_S)
		return (*(*(game_data->maps + game_data->pocketmon_row + 1)
				+ game_data->pocketmon_column));
	else if (keycode == KEY_D)
		return (*(*(game_data->maps + game_data->pocketmon_row)
				+ game_data->pocketmon_column + 1));
	else if (keycode == KEY_W)
		return (*(*(game_data->maps + game_data->pocketmon_row - 1)
				+ game_data->pocketmon_column));
	return ('B');
}

static void	move_pocketmon(t_game_data *game_data, int keycode,
	int p_row, int p_column)
{
	*(*(game_data->maps + p_row) + p_column) = '0';
	if (keycode == KEY_A)
	{
		*(*(game_data->maps + p_row) + p_column - 1) = 'P';
		game_data->pocketmon_column = p_column - 1;
	}
	if (keycode == KEY_S)
	{
		*(*(game_data->maps + p_row + 1) + p_column) = 'P';
		game_data->pocketmon_row = p_row + 1;
	}
	if (keycode == KEY_D)
	{
		*(*(game_data->maps + p_row)
				+ p_column + 1) = 'P';
		game_data->pocketmon_column = p_column + 1;
	}
	if (keycode == KEY_W)
	{
		*(*(game_data->maps + p_row - 1) + p_column) = 'P';
		game_data->pocketmon_row = p_row - 1;
	}
}

static void	move_pocketmon_and_change_map(t_game_data *game_data,
	t_mlx_data *mlx_data, int keycode)
{
	char	predicted_block;

	predicted_block = get_predicted_block(game_data, keycode);
	if (predicted_block == '0' || predicted_block == 'C')
	{
		if (predicted_block == 'C')
			game_data->coin_count --;
		move_pocketmon(game_data, keycode,
			game_data->pocketmon_row, game_data->pocketmon_column);
		ft_putstr_fd("current number of movements : ", 1);
		ft_putnbr_fd(++game_data->pocketmon_movement_count, 1);
		write(1, "\n", 1);
	}
	else if (predicted_block == 'E')
	{
		if (game_data->coin_count == 0)
		{
			mlx_destroy_window(mlx_data->mlx, mlx_data->win);
			ft_putstr_fd("current number of movements : ", 1);
			ft_putnbr_fd(++game_data->pocketmon_movement_count, 1);
			write(1, "\n", 1);
			exit(0);
		}
	}
}

int	event_key_hook(int keycode, t_all_data *all_data)
{
	t_mlx_data	*mlx_data;
	t_game_data	*game_data;

	mlx_data = &all_data->mlx_data;
	game_data = &all_data->game_data;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		exit(0);
	}
	if (keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D || keycode == KEY_W)
	{
		move_pocketmon_and_change_map(game_data, mlx_data, keycode);
		render_map(game_data->maps, mlx_data);
	}
	return (0);
}

int	event_closed_by_red_cross(int keycode, t_mlx_data *mlx_data)
{
	if (keycode != EVENT_ON_DESTROY)
		mlx_data = 0;
	exit (0);
	return (0);
}
