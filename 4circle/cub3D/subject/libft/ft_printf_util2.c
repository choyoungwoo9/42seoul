/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:48 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/11 09:33:04 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"
# include"libft.h"

void	reculsive_put_unsigned_nbr(unsigned int n, int fd)
{
	unsigned long long	num;
	char				tmp_ch;

	num = n;
	if (num == 0)
		return ;
	reculsive_put_unsigned_nbr(num / 10, fd);
	tmp_ch = num % 10 + '0';
	write(fd, &tmp_ch, 1);
}

void	ft_put_unsigned_nbr_fd(unsigned int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	reculsive_put_unsigned_nbr(n, fd);
}

int	find_int_digit(int nbr)
{
	long long	n;
	int			digit;

	digit = 0;
	n = nbr;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		digit ++;
		n = n * -1;
	}
	while (n != 0)
	{
		n = n / 10;
		digit ++;
	}
	return (digit);
}

int	find_unsigned_int_digit(unsigned int nbr)
{
	unsigned long long	n;
	int					digit;

	digit = 0;
	n = nbr;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		digit ++;
	}
	return (digit);
}
