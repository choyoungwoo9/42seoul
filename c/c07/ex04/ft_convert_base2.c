/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:46:46 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/15 19:35:58 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ignore_whitespace_and_find_sign(char *str, int *sign_counter)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '\t' || *(str + i) == '\n' || *(str + i) == '\v')
			i ++;
		else if (*(str + i) == '\f' || *(str + i) == '\r' || *(str + i) == ' ')
			i ++;
		else
			break ;
	}
	while (*(str + i))
	{
		if (*(str + i) == '-')
		{
			*sign_counter = *sign_counter + 1;
			i ++;
		}
		else if (*(str + i) == '+')
			i ++;
		else
			break ;
	}
	return (i);
}

int	check_index2(char *base, char ch, int *num_by_ref)
{
	int	i;

	i = 0;
	while (*(base + i))
	{
		if (ch == *(base + i))
		{
			*num_by_ref = i;
			return (1);
		}
		i ++;
	}
	return (0);
}

int	make_integer2(char *str, char *base, int base_length)
{
	int	i;
	int	result;
	int	num_by_ref;

	i = 0;
	result = 0;
	while (*(str + i))
	{
		if (check_index2(base, *(str + i), &num_by_ref))
		{
			result = result * base_length + num_by_ref;
			i ++;
		}
		else
			break ;
	}
	return (result);
}

int	ft_atoi_base(char *str, char *base)
{
	int			j;
	long long	k;
	int			sign_counter;
	int			base_length;

	base_length = 0;
	sign_counter = 0;
	while (*(base + base_length))
		base_length ++;
	j = ignore_whitespace_and_find_sign(str, &sign_counter);
	k = make_integer2(str + j, base, base_length);
	if (sign_counter % 2)
		k = k * -1;
	return (k);
}

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
