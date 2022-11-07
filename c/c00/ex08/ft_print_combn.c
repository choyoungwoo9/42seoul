/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:01:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/14 10:09:52 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	find_ar_size_2(char*ar)
{
	int	i;

	i = 0;
	while (*(ar + i))
	{
		i++;
	}
	return (i);
}

void	comb_write_2(char *ar, int max_depth)
{
	write(1, ar, max_depth);
	if (ar[0] == (10 - max_depth + '0'))
	{
		return ;
	}
	write(1, ", ", 2);
	return ;
}

void	travel_2(char *ar, int depth, int i)
{
	int	max_depth;

	max_depth = find_ar_size_2(ar);
	ar[depth - 1] = i + '0';
	if (depth == max_depth)
	{
		comb_write_2(ar, max_depth);
		if (i < 9)
		{
			travel_2(ar, depth, i + 1);
		}
		return ;
	}
	travel_2(ar, depth + 1, i + 1);
	if (i < 9 - (max_depth - depth))
	{
		travel_2(ar, depth, i + 1);
	}
	return ;
}

void	ft_print_combn(int n)
{
	char	ar[11];
	int		i;

	i = 0;
	while (i < n)
	{
		ar[i] = '0';
		i++;
	}
	ar[n] = '\0';
	travel_2(ar, 1, 0);
}
