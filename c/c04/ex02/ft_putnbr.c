/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:55:23 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/09 11:00:27 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	print_digit(int aa)
{
	char	ch;

	if (aa < 10)
	{
		ch = '0' + aa;
		write(1, &ch, 1);
	}
	else
	{
		print_digit(aa / 10);
		ch = '0' + aa % 10;
		write(1, &ch, 1);
	}
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	print_digit(nb);
}
