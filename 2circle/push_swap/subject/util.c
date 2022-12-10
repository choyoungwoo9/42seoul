/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:01:29 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/10 14:56:05 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

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
	while(*(str + index))
	{
		if(!(*(str + index) >= '0' && *(str + index) <= '9'))
			return 0;
		index ++;
	}
	*digit = index;
	return (1);
}

int	ft_atoll(const char *str, long long *tmp_ll)
{
	int			sign;
	int			digit;
	long long	result;

	sign = 1;
	if (*(str) == '-')
	{
		sign = -1;
		str ++;
	}
	if(!is_valid_digit_length(str, &digit))
		return 0;
	if(digit > 10)
		return 0;
	result = reculsive_atoll(str, digit, 1, sign);
	*tmp_ll = sign * result;
	return (1);
}

int	is_integer(char *argv, int *value)
{
	long long	tmp_ll;
	if(!ft_atoll(argv, &tmp_ll))
		return 0;
	if(tmp_ll < INT32_MIN || tmp_ll > INT32_MAX)
		return (0);
	*value = (int)tmp_ll;
	return (1);
}

int	is_duplicated(int value, t_stack *head)
{
	while(head)
	{
		if(head->number == value)
		{
			return (1);
		}
		head = head->next;
	}
	return (0);
}