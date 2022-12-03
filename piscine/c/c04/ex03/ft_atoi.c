/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:42:55 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/09 11:02:56 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	find_whitespace(char *str)
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
	return (i);
}

int	find_sign(char *str, int *sign_counter)
{
	int	i;

	i = 0;
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

int	make_integer(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (*(str + i))
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
		{
			result = result * 10 + (*(str + i) - '0');
			i ++;
		}
		else
			break ;
	}
	return (result);
}

int	ft_atoi(char *str)
{
	int	i;
	int	j;
	int	k;
	int	sign_counter;

	i = find_whitespace(str);
	j = find_sign(str + i, &sign_counter);
	k = make_integer(str + i + j);
	if (sign_counter % 2)
		k = k * -1;
	return (k);
}
