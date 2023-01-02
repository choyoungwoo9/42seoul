/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check_valid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:58:51 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/24 20:27:37 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_check(char **maps)
{
	if (!is_minimal_map_size(maps))
		print_error_exit("NOT_VALID_MAP_SIZE");
	if (!is_rectangular_map(maps))
		print_error_exit("NOT_RECTANGULAR_MAP");
	if (!is_map_surrounded_wall(maps))
		print_error_exit("NOT_SURROUNED_WALL_MAP");
	if (!is_have_valid_path(maps))
		print_error_exit("NOT_VALID_MAP_PATH");
}

static void	component_check(char **maps)
{
	if (is_have_another_component(maps))
		print_error_exit("HAVE_ANOTHER_COMPONENT");
	if (!is_one_pocketmon(maps))
		print_error_exit("POCKETMON_IS_NOT_ONE");
	if (!is_one_door(maps))
		print_error_exit("DOOR_IS_NOT_ONE");
	if (!is_have_at_least_one_coin(maps))
		print_error_exit("ZERO_COIN");
}

void	check_valid_map(t_game_data game_data)
{
	component_check(game_data.maps);
	map_check(game_data.maps);
}
