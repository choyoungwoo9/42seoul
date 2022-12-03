/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:00:25 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/15 14:18:01 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (*(src + i))
		i ++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*(src + i))
	{
		*(str + i) = *(src + i);
		i ++;
	}
	*(str + i) = '\0';
	return (str);
}
