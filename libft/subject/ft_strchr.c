/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:20:07 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/09 12:38:00 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != 0)
	{
		if (*(s + i) == c)
		{
			return ((char *)(s + i));
		}
		i ++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (0);
}
