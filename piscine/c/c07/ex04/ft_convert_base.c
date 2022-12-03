/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:19:10 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/15 20:26:32 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	ft_atoi_base(char *str, char *base);

int	same_base_check(char *base, char ch);

int	basecheck(char *base)
{
	int	base_length;

	base_length = 0;
	while (*(base + base_length))
	{
		if (*(base + base_length) == '-' || *(base + base_length) == '+')
			return (1);
		if (same_base_check(base, *(base + base_length)))
			return (1);
		base_length ++;
	}
	if (base_length <= 1)
	{
		return (1);
	}
	return (0);
}

void	recursive_putnbr_base(int nbr, char *base, char *array, int count)
{
	long long	nb;
	int			base_length;

	nb = nbr;
	base_length = 0;
	while (*(base + base_length))
		base_length ++;
	if (nb < 0)
	{
		*array = '-';
		nb = nb * -1;
	}
	if (nb > 0)
	{
		recursive_putnbr_base(nb / base_length, base, array, -- count);
		*(array + count) = *(base + (nb % base_length));
	}
}

int	find_digit(int num, int length)
{
	long long	number;
	int			digit;

	number = num;
	digit = 1;
	if (number < 0)
	{
		digit ++;
		number = number * -1;
	}
	while (number >= length)
	{
		number = number / length;
		digit ++;
	}
	return (digit);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		tem_num;
	char	*array;
	int		to_base_length;
	int		digit;

	if (basecheck(base_from) || basecheck(base_to))
		return (NULL);
	to_base_length = 0;
	while (*(base_to + to_base_length))
		to_base_length ++;
	tem_num = ft_atoi_base(nbr, base_from);
	digit = find_digit(tem_num, to_base_length);
	array = (char *)malloc(digit + 1);
	*(array + digit) = '\0';
	if (tem_num == 0)
	{
		*array = *base_to;
		return (array);
	}
	recursive_putnbr_base(tem_num, base_to, array, digit);
	return (array);
}
