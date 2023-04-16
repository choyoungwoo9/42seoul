/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:36:48 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/11 09:33:10 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"
# include"libft.h"

int	reculsive_write_hexnbr(unsigned long long num, int length)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (num == 0)
		return (length);
	length = reculsive_write_hexnbr(num / 16, length);
	write(1, hex + num % 16, 1);
	return (length + 1);
}

int	put_hexnbr(unsigned long long tmp)
{
	int	length;

	if (tmp == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	length = 0;
	length = reculsive_write_hexnbr(tmp, 0);
	return (length);
}

int	reculsive_write_large_hexnbr(unsigned long long num, int length)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (num == 0)
		return (length);
	length = reculsive_write_large_hexnbr(num / 16, length);
	write(1, hex + num % 16, 1);
	return (length + 1);
}

int	put_large_hexnbr(unsigned long long tmp)
{
	int	length;

	if (tmp == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	length = 0;
	length = reculsive_write_large_hexnbr(tmp, 0);
	return (length);
}
