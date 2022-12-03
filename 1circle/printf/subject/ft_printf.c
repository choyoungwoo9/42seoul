/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:28:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/26 18:27:45 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	categorize_type(const char *format, int *length, va_list ap)
{
	char	type;

	type = *format;
	if (type == 'c' || type == 'd' || type == 'i')
		check_type1(type, length, ap);
	else if (type == 'x' || type == 'X')
		check_type2(type, length, ap);
	else if (type == '%' || type == 'u')
		check_type3(type, length, ap);
	else if (type == 's')
		check_type4(type, length, ap);
	else if (type == 'p')
		check_type5(type, length, ap);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		length;

	length = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format ++;
			categorize_type(format, &length, ap);
		}
		else
		{
			write(1, format, 1);
			length ++;
		}
		format ++;
	}
	va_end(ap);
	return (length);
}
