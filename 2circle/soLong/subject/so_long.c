/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:57:18 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 17:44:38 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_all_data	all_data;

	if (argc != 2)
		return (0);
	get_map(&all_data.game_data, *(argv + 1));
	check_valid_map(all_data.game_data);
	set_game_data_from_map(&all_data.game_data);
	make_mlx_instance_and_window(&all_data);
	render_map(all_data.game_data.maps, &all_data.mlx_data);
	mlx_key_hook(all_data.mlx_data.win, event_key_hook, &all_data);
	mlx_hook(all_data.mlx_data.win, EVENT_ON_DESTROY,
		0, event_closed_by_red_cross, &all_data.mlx_data);
	mlx_loop(all_data.mlx_data.mlx);
	return (0);
}
