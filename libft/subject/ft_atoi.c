/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:58:06 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/10 16:46:12 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	reculsive_atoi(const char *str, int digit, int place_value)
{
	if (digit == 0)
		return (0);
	return (reculsive_atoi(str, digit - 1, place_value * 10)
		+ (*(str + digit - 1) - '0') * place_value);
}

int	find_digit(const char *str)
{
	int	index;

	index = 0;
	while (*(str + index) >= '0' && *(str + index) <= '9')
		index ++;
	return (index);
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			digit;
	long long	result;

	sign = 1;
	while (1)
	{
		if (*(str) == '\t' || *(str) == '\n' || *(str) == '\v' || *(str) == '\f'
			|| *(str) == '\r' || *(str) == ' ')
			str ++;
		else
			break ;
	}
	if (*(str) == '-' || *(str) == '+')
	{
		if (*(str) == '-')
			sign = -1;
		str ++;
	}
	digit = find_digit(str);
	result = reculsive_atoi(str, digit, 1);
	return (sign * result);
}
