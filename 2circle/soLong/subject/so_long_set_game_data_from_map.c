/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_set_game_data_from_map.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:26:24 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 15:21:51 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_pocketmon_exit_coin_data(t_game_data *game_data,
	char block, int i, int j)
{
	if (block == 'P')
	{
		game_data->pocketmon_row = i;
		game_data->pocketmon_column = j;
	}
	if (block == 'E')
	{
		game_data->exit_row = i;
		game_data->exit_column = j;
	}
	if (block == 'C')
		(game_data->coin_count)++;
}

void	set_game_data_from_map(t_game_data *game_data)
{
	int	i;
	int	j;

	game_data->coin_count = 0;
	game_data->pocketmon_movement_count = 0;
	i = -1;
	while (*(game_data->maps + ++i))
	{
		j = -1;
		while (*(*(game_data->maps + i) + ++j))
		{
			set_pocketmon_exit_coin_data(game_data,
				*(*(game_data->maps + i) + j), i, j);
		}
	}
	game_data->row = i;
	game_data->column = j;
}
