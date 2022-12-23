/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check_valid_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:58:51 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 15:20:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_minimal_map_size(char **maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
			j ++;
		i ++;
	}
	if (i < 3 || j < 3)
		return (0);
	return (1);
}

int	is_rectangular_map(char **maps)
{
	int	i;
	int	j;
	int	column;

	column = -1;
	i = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
			j ++;
		if (column == -1)
			column = j;
		else
		{
			if (column != j)
				return (0);
		}
		i ++;
	}
	return (1);
}

int	is_map_surrounded_wall(char **maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			if (i == 0 || j == 0
				|| *(*(maps + i) + j + 1) == '\0'
				|| *(maps + i + 1) == NULL)
			{
				if (*(*(maps + i) + j) != '1')
					return (0);
			}
			j ++;
		}
		i ++;
	}
	return (1);
}
