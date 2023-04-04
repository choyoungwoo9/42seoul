/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:52:35 by yuikim            #+#    #+#             */
/*   Updated: 2022/12/23 17:46:45 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(va_list ap)
{
	char	temp;

	temp = va_arg(ap, int);
	write(1, &temp, 1);
	return (1);
}

int	print_s(va_list ap)
{
	char	*temp;

	temp = va_arg(ap, char *);
	if (temp == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, temp, ft_strlen2(temp));
	return (ft_strlen2(temp));
}

int	print_p(va_list ap)
{
	unsigned long long	temp;
	int					len;

	temp = va_arg(ap, unsigned long long);
	write(1, "0x", 2);
	len = ft_find_number_figure(temp, 16);
	ft_write_base(temp, len, "0123456789abcdef");
	return (len + 2);
}

int	print_d(va_list ap)
{
	int	temp;

	temp = va_arg(ap, int);
	ft_putnbr_fd(temp, 1);
	return (ft_find_figure(temp));
}

int	print_u(va_list ap)
{
	unsigned int	temp;
	int				len;

	temp = va_arg(ap, unsigned int);
	len = ft_find_number_figure(temp, 10);
	ft_write_base(temp, len, "0123456789");
	return (len);
}
