/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:25:02 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 16:31:35 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_all_coin(char **maps)
{
	int	coin_count;
	int	i;
	int	j;

	coin_count = 0;
	i = -1;
	while (*(maps + ++i))
	{
		j = -1;
		while (*(*(maps + i) + ++j))
		{
			if (*(*(maps + i) + j) == 'C')
				coin_count ++;
		}
	}
	return (coin_count);
}

void	get_pocketmon_row_column(char **maps,
	int *pocketmon_row, int *pocketmon_column)
{
	int	i;
	int	j;

	i = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			if (*(*(maps + i) + j) == 'P')
			{
				*pocketmon_row = i;
				*pocketmon_column = j;
			}
			j ++;
		}
		i ++;
	}
}

char	**copy_map(char **map)
{
	char	**copied_map;
	int		i;

	i = -1;
	while (*(map + ++i))
	{
	}
	copied_map = malloc(sizeof(char *) * (i + 1));
	*(copied_map + i) = NULL;
	while (-- i >= 0)
		*(copied_map + i) = ft_strdup(*(map + i));
	return (copied_map);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (*(map + (++i)))
		free(*(map + i));
	free(map);
}

void	print_error_exit(char *message)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(message, 1);
	exit(0);
}
