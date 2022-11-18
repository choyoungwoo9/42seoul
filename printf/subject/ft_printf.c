/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:28:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/18 13:59:36 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdarg.h>
#include<unistd.h>
#include"libft/libft.h"
#include"ft_printf.h"

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
				char ch = va_arg(ap, int);
				write(1, &ch, 1);
			}
			else if (*(format) == 's')
			{
				char *tmp = va_arg(ap, char *);
				write(1, tmp, ft_strlen(tmp));
			}
			else if (*(format) == 'p')
			{
				//char tmp = va_arg(ap, char);
				write(1, format, 1);
			}
			else if (*(format) == 'd')
			{
				int tmp = va_arg(ap, int);
				ft_putnbr_fd(tmp, 1);
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
	printf("abc + %c, %s, %d\n", 'z', "string", 4);
	ft_printf("abc + %c, %s, %d\n", 'z', "string", 4);
	return (0);
}
