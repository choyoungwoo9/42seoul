/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:18:13 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/15 14:25:01 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	*ft_range(int min, int max)
{
	int	*array;
	int	i;

	if (max <= min)
		return (NULL);
	array = (int *)malloc(sizeof(int) * (max - min));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < (max - min))
	{
		*(array + i) = min + i;
		i ++;
	}
	return (array);
}
