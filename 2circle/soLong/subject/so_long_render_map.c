/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:20:32 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 17:44:46 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_by_map_block(char block, t_mlx_data *mlx_data, int i, int j)
{
	int		img_width;
	int		img_height;
	void	*img;

	if (block == '0')
		img = mlx_xpm_file_to_image(mlx_data->mlx,
				GROUND_PATH, &img_width, &img_height);
	if (block == '1')
		img = mlx_xpm_file_to_image(mlx_data->mlx,
				LAVA_PATH, &img_width, &img_height);
	if (block == 'C')
	{
		img = mlx_xpm_file_to_image(mlx_data->mlx,
				COIN_SMALL_PATH, &img_width, &img_height);
		mlx_put_image_to_window(mlx_data->mlx,
			mlx_data->win, img, j * 64 + 17, i * 64 + 17);
		return ;
	}
	if (block == 'E')
		img = mlx_xpm_file_to_image(mlx_data->mlx,
				DOOR_PATH, &img_width, &img_height);
	if (block == 'P')
		img = mlx_xpm_file_to_image(mlx_data->mlx,
				POCKETMON_FRONT_PATH, &img_width, &img_height);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, img, j * 64, i * 64);
}

void	render_map(char **maps, t_mlx_data *mlx_data)
{
	int		img_width;
	int		img_height;
	void	*img;
	int		i;
	int		j;

	i = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			img = mlx_xpm_file_to_image(mlx_data->mlx,
					GROUND_PATH, &img_width, &img_height);
			mlx_put_image_to_window(mlx_data->mlx, mlx_data->win,
				img, j * 64, i * 64);
			render_by_map_block(*(*(maps + i) + j), mlx_data, i, j);
			j ++;
		}
		i ++;
	}
}
