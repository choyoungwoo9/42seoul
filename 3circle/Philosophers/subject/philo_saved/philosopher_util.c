/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 10:39:41 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/12 17:37:50 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static long long	reculsive_atoll(const char *str, int digit,
	long long place_value, int sign)
{
	long long	ret_ll;

	if (digit == 0)
		return (0);
	ret_ll = reculsive_atoll(str, digit - 1, place_value * 10, sign)
		+ ((*(str + digit - 1) - '0') * place_value);
	return (ret_ll);
}

static int	is_valid_digit_length(const char *str, int *digit)
{
	int	index;

	index = 0;
	while (*(str + index))
	{
		if (*(str + index) < '0' || *(str + index) > '9')
			return (0);
		index ++;
	}
	*digit = index;
	return (1);
}

static int	ft_atoll(const char *str, long long *tmp_ll)
{
	int			sign;
	int			digit;
	long long	result;

	sign = 1;
	if (*(str) == '-' || *(str) == '+')
	{
		if (*(str) == '-')
			sign = -1;
		str ++;
	}
	if (!is_valid_digit_length(str, &digit))
		return (0);
	if (digit > 10 || digit == 0)
		return (0);
	result = reculsive_atoll(str, digit, 1, sign);
	*tmp_ll = sign * result;
	return (1);
}

int	is_integer(char *argv, int *value)
{
	long long	tmp_ll;

	tmp_ll = INT32_MAX + (long long)1;
	if (!ft_atoll(argv, &tmp_ll))
		return (0);
	if (tmp_ll < INT32_MIN || tmp_ll > INT32_MAX)
		return (0);
	*value = (int)tmp_ll;
	return (1);
}