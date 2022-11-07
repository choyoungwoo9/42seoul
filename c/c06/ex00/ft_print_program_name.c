/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:22:00 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/10 10:28:02 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 1)
		j = 0;
	i = 0;
	while (*(*argv + i))
	{
		write(1, *argv + i, 1);
		i ++;
	}
	write(1, "\n", 1);
	return (0);
}
