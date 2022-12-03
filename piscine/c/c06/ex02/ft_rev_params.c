/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev.params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:15:01 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/10 10:17:36 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = argc - 1;
	while (i > 0)
	{
		j = 0;
		while (*(*(argv + i) + j))
		{
			write(1, argv[i] + j, 1);
			j ++;
		}
		write(1, "\n", 1);
		i --;
	}
	return (0);
}
