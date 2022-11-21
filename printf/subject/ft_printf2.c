/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:28:20 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/21 10:53:15 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/////////////주석 지울 것
#include<stdio.h>

#include<stdarg.h>
#include<unistd.h>
#include"ft_printf.h"

///////////////////x and p
int reculsive_write_hexnbr(unsigned long long num, int length)
{
	char *hex = "0123456789abcdef";
	
	if(num == 0)
		return length;

	length = reculsive_write_hexnbr(num / 16, length);	
	write(1, hex + num % 16, 1);
	return length + 1;
}

int	put_hexnbr(unsigned long long tmp)
{
	int length;
	
	if(tmp == 0)
	{
		write(1, "0", 1);
		return 1;
	}
	length = 0;
	length = reculsive_write_hexnbr(tmp, 0);
	return length;
}
///////////////////x and p
int reculsive_write_large_hexnbr(unsigned long long num, int length)
{
	char *hex = "0123456789ABCDEF";
	
	if(num == 0)
		return length;

	length = reculsive_write_large_hexnbr(num / 16, length);
	write(1, hex + num % 16, 1);
	return length + 1;
}

int	put_large_hexnbr(unsigned long long tmp)
{
	int length;
	
	if(tmp == 0)
	{
		write(1, "0", 1);
		return 1;
	}
	length = 0;
	length = reculsive_write_large_hexnbr(tmp, 0);
	return length;
}

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

int find_int_digit(int nbr)
{
	long long n;
	int digit;

	digit = 0;
	n = nbr;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		digit ++;
		n = n * -1;
	}
	while(n != 0)
	{
		n = n / 10;
		digit ++;
	}
	return digit;
}

int find_unsigned_int_digit(unsigned int nbr)
{
	unsigned long long n;
	int digit;

	digit = 0;
	n = nbr;
	if (n == 0)
		return (1);
	while(n != 0)
	{
		n = n / 10;
		digit ++;
	}
	return digit;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int length;
	
	length = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format ++;
			if (*(format) == '%')
			{
				write(1, format, 1);
				length ++;
			}
			else if (*(format) == 'c')
			{
				char tmp = va_arg(ap, int);
				write(1, &tmp, 1);
				length ++;
			}
			else if (*(format) == 's')
			{
				char *tmp = va_arg(ap, char *);
				if(tmp == 0)
				{
					write(1, "(null)", 6);
					length = length + 6;
				}
				else
				{
					write(1, tmp, ft_strlen(tmp));
					length = length + ft_strlen(tmp);
				}
			}
			else if (*(format) == 'p')
			{
				void *ptr = va_arg(ap, void *);
				write(1, "0x", 2);
				length += 2;
				if(ptr == 0)
				{
					write(1, "0", 1);
					length += 1;
				}
				else
					length = length + put_hexnbr((unsigned long long)ptr);
			}
			else if (*(format) == 'd')
			{
				int tmp = va_arg(ap, int);
				length = length + find_int_digit(tmp);
				ft_putnbr_fd(tmp, 1);
			}
			else if (*(format) == 'i')
			{
				int tmp = va_arg(ap, int);
				length = length + find_int_digit(tmp);
				ft_putnbr_fd(tmp, 1);
			}
			else if (*(format) == 'u')
			{
				unsigned long long tmp = va_arg(ap, int);
				length = length + find_unsigned_int_digit(tmp);
				ft_put_unsigned_nbr_fd(tmp, 1);
			}
			else if (*(format) == 'x')
			{
				unsigned int tmp = va_arg(ap, int);
				length = length + put_hexnbr(tmp);
			}
			else if (*(format) == 'X')
			{
				unsigned int tmp = va_arg(ap, int);
				length = length + put_large_hexnbr(tmp);
			}
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
