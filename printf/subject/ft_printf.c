/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:28:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/17 16:49:21 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdarg.h>
#include<unistd.h>
#include"libft/libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format ++;
			if (*(format) == '%')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'c')
			{
				write(1, format, 1);
			}
			else if (*(format) == 's')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'p')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'd')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'i')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'u')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'x')
			{
				write(1, format, 1);
			}
			else if (*(format) == 'X')
			{
				write(1, format, 1);
			}
		}
		else
			write(1, format, 1);
		format ++;
	}
	va_end(ap);
	return (0);
}

int main()
{
	printf("%d, %s\n", 214748364, (char *)0);
	ft_printf("abc + %d, %d", 1, 4);
	return (0);
}
