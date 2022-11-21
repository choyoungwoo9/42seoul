/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:28:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/21 10:50:18 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdarg.h>
#include<unistd.h>
#include"ft_printf.h"


void check_type1(char format_type, int *length, va_list ap)
{
	char	tmp_c;
	int		tmp_i;

	if (format_type == 'c')
	{
		tmp_c = va_arg(ap, int);
		write(1, &tmp_c, 1);
		(*length)++;
	}
	else if (format_type == 'd')
	{
		tmp_i = va_arg(ap, int);
		(*length) = (*length) + find_int_digit(tmp_i);
		ft_putnbr_fd(tmp_i, 1);
	}
	else if (format_type == 'i')
	{
		tmp_i = va_arg(ap, int);
		*length = *length + find_int_digit(tmp_i);
		ft_putnbr_fd(tmp_i, 1);
	}
}

void	check_type2(char format_type, int *length, va_list ap)
{
	unsigned int		tmp_ui;
	char	*tmp_p;
	
	if (format_type == 'x')
	{
		tmp_ui = va_arg(ap, int);
		*length = *length + put_hexnbr(tmp_ui);
	}
	else if (format_type == 'X')
	{
		tmp_ui = va_arg(ap, int);
		*length = *length + put_large_hexnbr(tmp_ui);
	}
	else if (format_type == 's')
	{
		tmp_p = va_arg(ap, char *);
		if (tmp_p == 0)
		{
			write(1, "(null)", 6);
			(*length) += 6;
		}
		else
		{
			write(1, tmp_p, ft_strlen(tmp_p));
			(*length) = (*length) + ft_strlen(tmp_p);
		}
	}
}

void	check_type3(char format_type, int *length, va_list ap)
{
	void				*tmp_p;
	unsigned long long	tmp_ull;

	if (format_type == '%')
	{
		write(1, &format_type, 1);
		(*length)++;
	}
	else if (format_type == 'p')
	{
		tmp_p = va_arg(ap, void *);
		write(1, "0x", 2);
		(*length) += 2;
		if (tmp_p == 0)
		{
			write(1, "0", 1);
			(*length) += 1;
		}
		else
			(*length) = (*length) + put_hexnbr((unsigned long long)tmp_p);
	}
	if (format_type == 'u')
	{
		tmp_ull = va_arg(ap, int);
		*length = *length + find_unsigned_int_digit(tmp_ull);
		ft_put_unsigned_nbr_fd(tmp_ull, 1);
	}
}

void	categorize_type(const char *type, int *length, va_list ap)
{
	char	tp;

	tp = *type;
	if (tp == 'c' || tp == 'd' || tp == 'i')
		check_type1(tp, length, ap);
	else if (tp == 'x' || tp == 'X' || tp == 's')
		check_type2(tp, length, ap);
	else if (tp == '%' || tp == 'p' || tp == 'u')
		check_type3(tp, length, ap);
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

// int main()
// {
// 	printf("%d, %s\n", 214748364, (char *)0);
// 	printf("abc + %c, %s, %d\n", 'z', "string", 4);
// 	ft_printf("abc + %c, %s, %d\n", 'z', "string", 4);
// 	return (0);
// }
