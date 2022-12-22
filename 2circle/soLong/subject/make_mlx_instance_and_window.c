/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mlx_instance_and_window.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:45:45 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/22 09:58:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void make_mlx_instance_and_window(t_all_data *all_data)
{
	t_mlx_data *mlx_data = &all_data->mlx_data;
	t_game_data *game_data = &all_data->game_data;
	mlx_data->mlx = mlx_init();
	mlx_data->win = mlx_new_window(mlx_data->mlx, 640, 640, "so_long");
}