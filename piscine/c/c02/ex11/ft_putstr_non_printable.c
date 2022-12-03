/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:11:29 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/11 12:09:16 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	print_non_printable(char *str)
{
	char			*hex_value;
	unsigned char	hex_array[3];

	hex_value = "0123456789abcdef";
	hex_array[0] = '\\';
	hex_array[1] = *(hex_value + (unsigned char)*str / 16);
	hex_array[2] = *(hex_value + (unsigned char)*str % 16);
	write(1, hex_array, 3);
}

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) < ' ' || *(str + i) == 127)
			print_non_printable(str + i);
		else
			write(1, str + i, 1);
		i ++;
	}
}
