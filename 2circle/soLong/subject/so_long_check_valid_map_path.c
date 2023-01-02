/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check_valid_map_path.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:44:02 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/24 16:48:56 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_is_have_valid_exit_by_dfs(char **map_copy,
	int p_row, int p_column)
{
	if (*(*(map_copy + p_row) + p_column) == 'E')
		return (1);
	if (*(*(map_copy + p_row) + p_column) == '1')
		return (0);
	*(*(map_copy + p_row) + p_column) = '1';
	if (check_is_have_valid_exit_by_dfs(map_copy, p_row + 1, p_column)
		|| check_is_have_valid_exit_by_dfs(map_copy, p_row - 1, p_column)
		|| check_is_have_valid_exit_by_dfs(map_copy, p_row, p_column + 1)
		|| check_is_have_valid_exit_by_dfs(map_copy, p_row, p_column - 1))
		return (1);
	return (0);
}

static int	is_have_valid_exit_path(char **maps)
{
	int		pocketmon_row;
	int		pocketmon_column;
	char	**copied_map;

	get_pocketmon_row_column(maps, &pocketmon_row, &pocketmon_column);
	copied_map = copy_map(maps);
	if (!check_is_have_valid_exit_by_dfs(
			copied_map, pocketmon_row, pocketmon_column))
	{
		free_map(copied_map);
		return (0);
	}
	free_map(copied_map);
	return (1);
}

static void	count_coin_by_dfs(char **map_copy, int p_row,
	int p_column, int *coin_coint)
{
	if (*(*(map_copy + p_row) + p_column) == '1')
		return ;
	if (*(*(map_copy + p_row) + p_column) == 'E')
		return ;
	if (*(*(map_copy + p_row) + p_column) == 'C')
		(*coin_coint)++;
	*(*(map_copy + p_row) + p_column) = '1';
	count_coin_by_dfs(map_copy, p_row + 1, p_column, coin_coint);
	count_coin_by_dfs(map_copy, p_row - 1, p_column, coin_coint);
	count_coin_by_dfs(map_copy, p_row, p_column + 1, coin_coint);
	count_coin_by_dfs(map_copy, p_row, p_column - 1, coin_coint);
	return ;
}

static int	is_have_valid_coin_path(char **maps)
{
	int		pocketmon_row;
	int		pocketmon_column;
	char	**copied_map;
	int		valid_coin_count;

	get_pocketmon_row_column(maps, &pocketmon_row, &pocketmon_column);
	copied_map = copy_map(maps);
	valid_coin_count = 0;
	count_coin_by_dfs(copied_map, pocketmon_row,
		pocketmon_column, &valid_coin_count);
	free_map(copied_map);
	if (count_all_coin(maps) == valid_coin_count)
		return (1);
	else
		return (0);
}

int	is_have_valid_path(char **maps)
{
	if (!is_have_valid_exit_path(maps))
		return (0);
	if (!is_have_valid_coin_path(maps))
		return (0);
	return (1);
}
