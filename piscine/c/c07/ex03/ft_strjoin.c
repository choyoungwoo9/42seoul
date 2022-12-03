/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:59:57 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/15 16:38:52 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	find_size(int size, char **strs, char *sep)
{
	int	all_str_size;
	int	i;
	int	j;

	all_str_size = 0;
	i = -1;
	j = -1;
	while (++i < size)
	{
		j = -1;
		while (*(*(strs + i) + ++j))
			all_str_size ++;
		if (i < size - 1)
		{
			j = -1;
			while (*(sep + ++j))
			{
				all_str_size ++;
			}
		}
	}
	all_str_size ++;
	return (all_str_size);
}

void	assign_str(char *result_str, int size, char **strs, char *sep)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	while (++i < size)
	{
		j = -1;
		while (*(*(strs + i) + ++j))
			*(result_str + ++k) = *(*(strs + i) + j);
		j = -1;
		while (*(sep + ++j) && i < size - 1)
			*(result_str + ++k) = *(sep + j);
	}
	*(result_str + ++k) = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*result_str;
	int		i;

	i = 0;
	if (size == 0)
	{
		result_str = (char *)malloc(sizeof(char) * 1);
		*result_str = '\0';
		return (result_str);
	}
	result_str = (char *)malloc(sizeof(char) * find_size(size, strs, sep));
	assign_str(result_str, size, strs, sep);
	return (result_str);
}
