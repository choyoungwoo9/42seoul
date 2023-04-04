/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:48:52 by yuikim            #+#    #+#             */
/*   Updated: 2022/12/24 15:24:56 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_find_number_figure(unsigned long long n1, unsigned long long base_len)
{
	int	i;

	i = 0;
	while (1)
	{
		i++;
		if (n1 / base_len == 0)
			return (i);
		n1 = n1 / base_len;
	}
	return (0);
}

void	ft_write_base(unsigned long long num, int count, char *base)
{
	int	base_len;

	base_len = ft_strlen2(base);
	if (count != 0)
	{
		ft_write_base(num / base_len, count - 1, base);
		write(1, &base[num % base_len], 1);
	}		
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	digit;

	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nb, fd);
	}
	else if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		digit = nb % 10 + '0';
		write(fd, &digit, 1);
	}
	else
	{
		digit = nb + '0';
		write(fd, &digit, 1);
	}
}

int	ft_find_figure(long long n)
{
	int			i;
	long long	n1;

	n1 = (long long)n;
	if (n1 < 0)
		return (ft_find_figure(-n1) + 1);
	i = 0;
	while (1)
	{
		i++;
		if (n1 / 10 == 0)
			return (i);
		n1 = n1 / 10;
	}
	return (0);
}
