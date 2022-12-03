/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:56:00 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/19 15:06:07 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	same_base_check(char *base, char ch)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (*(base + i))
	{
		if (*(base + i) == ch)
			counter ++;
		i ++;
	}
	if (counter == 1)
		return (0);
	else
		return (1);
}

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

void recursive_putnbr_base(int nbr, char *base, int count)
{
	long long	nb;
	int			base_length;

	nb = nbr;
	base_length = 0;
	if (basecheck(base))
		return ;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
	}
	while (*(base + base_length))
		base_length ++;
	if(count == 0 && nbr == 0)
	{
		write(1, base, 1);
	}
	if (nb > 0)
	{
		count ++;
		recursive_putnbr_base(nb / base_length, base, count);
		write(1, base + (nb % base_length), 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	recursive_putnbr_base(nbr, base, 0);
}
