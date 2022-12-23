/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_check_valid_component.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:58:51 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 15:47:52 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_one_pocketmon(char **maps)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			if (*(*(maps + i) + j) == 'P')
				count ++;
			j ++;
		}
		i ++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int	is_one_door(char **maps)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			if (*(*(maps + i) + j) == 'E')
				count ++;
			j ++;
		}
		i ++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int	is_have_at_least_one_coin(char **maps)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			if (*(*(maps + i) + j) == 'C')
				count ++;
			j ++;
		}
		i ++;
	}
	if (count > 1)
		return (1);
	else
		return (0);
}

int	is_have_another_component(char **maps)
{
	int		i;
	int		j;
	char	component;

	i = 0;
	j = 0;
	while (*(maps + i))
	{
		j = 0;
		while (*(*(maps + i) + j))
		{
			component = *(*(maps + i) + j);
			if (component != '0' && component != '1'
				&& component != 'C' && component != 'E' && component != 'P')
				return (1);
			j ++;
		}
		i ++;
	}
	return (0);
}
