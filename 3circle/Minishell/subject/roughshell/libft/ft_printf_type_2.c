/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:56:59 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/28 08:57:01 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_x(va_list ap)
{
	unsigned int	temp;
	int				len;

	temp = va_arg(ap, unsigned int);
	len = ft_find_number_figure(temp, 16);
	ft_write_base(temp, len, "0123456789abcdef");
	return (len);
}

int	print_upper_x(va_list ap)
{
	unsigned int	temp;
	int				len;

	temp = va_arg(ap, unsigned int);
	len = ft_find_number_figure(temp, 16);
	ft_write_base(temp, len, "0123456789ABCDEF");
	return (len);
}
