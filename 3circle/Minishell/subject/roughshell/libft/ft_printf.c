/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:49:05 by yuikim            #+#    #+#             */
/*   Updated: 2022/11/28 09:47:44 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_type(va_list ap, const char *input)
{
	if (*input == 'c')
		return (print_c(ap));
	if (*input == 's')
		return (print_s(ap));
	if (*input == 'p')
		return (print_p(ap));
	if (*input == 'd')
		return (print_d(ap));
	if (*input == 'i')
		return (print_d(ap));
	if (*input == 'u')
		return (print_u(ap));
	if (*input == 'x')
		return (print_x(ap));
	if (*input == 'X')
		return (print_upper_x(ap));
	if (*input == '%')
	{
		write(1, &(*input), 1);
		return (1);
	}
	return (-1);
}

int	ft_check_input(va_list ap, const char *input)
{
	int	i;
	int	len;

	i = 0;
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			len = ft_strlen_type(ap, input);
			if (len == -1)
				return (-1);
			i += len;
		}
		else
		{
			if (write(1, input, 1) == -1)
				return (-1);
			i++;
		}
		input++;
	}
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		answer;

	va_start(ap, input);
	answer = ft_check_input(ap, input);
	va_end(ap);
	return (answer);
}
