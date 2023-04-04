/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:55:36 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/21 18:56:11 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_digit(char ch)
{
	if ('0' <= ch && ch <= '9')
		return (1);
	return (0);
}

static void	exit_now(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

int	ft_atoi(char *str)
{
	long long	num;
	int			i;
	int			sign;

	num = 0;
	sign = 1;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (check_digit(str[i]))
	{
		num = (str[i] - '0') + num * 10;
		i++;
	}
	if (sign * num > 2147483647 || sign * num < -2147483648)
		exit_now("Error\n");
	return (sign * num);
}
