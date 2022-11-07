/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:51:21 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/03 21:52:46 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	spt_comb(int i, int j)
{
	char	comb_array[7];

	comb_array[0] = i / 10 + '0';
	comb_array[1] = i % 10 + '0';
	comb_array[2] = ' ';
	comb_array[3] = j / 10 + '0';
	comb_array[4] = j % 10 + '0';
	comb_array[5] = ',';
	comb_array[6] = ' ';
	if (i == 98 && j == 99)
	{
		write(1, comb_array, 5);
	}
	else
	{
		write(1, comb_array, 7);
	}
	return ;
}

void	ft_print_comb2(void)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < 99)
	{
		j = i + 1;
		while (j < 100)
		{
			spt_comb(i, j);
			j ++;
		}
		i ++;
	}
	return ;
}
