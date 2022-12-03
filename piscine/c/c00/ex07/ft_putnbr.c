/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:24:15 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/03 10:05:32 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	count_place(int nb)
{
	int	place_count;

	place_count = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		place_count ++;
	}
	return (place_count);
}

int	print_each_num(nb, place_count)
{
	int		div_value;
	int		return_value;
	int		value;
	char	ch_value;

	div_value = 1;
	while (place_count != 1)
	{
		div_value = div_value * 10;
		place_count --;
	}
	return_value = nb % div_value;
	value = nb / div_value;
	ch_value = value + '0';
	write(1, &ch_value, 1);
	return (return_value);
}

void	ft_putnbr(int nb)
{
	int	place_count;

	place_count = count_place(nb);
	if (nb <= 0)
	{
		if (nb == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		if (nb == 0)
		{
			write(1, "0", 1);
			return ;
		}	
		write(1, "-", 1);
		nb = nb * -1;
	}
	while (place_count != 0)
	{
		nb = print_each_num(nb, place_count);
		place_count --;
	}
	return ;
}
