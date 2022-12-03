/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:35:39 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/20 15:56:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	src_size;
	unsigned int	i;

	i = 0;
	src_size = 0;
	while (*(src + src_size))
	{
		src_size ++;
	}
	while (i < n)
	{
		if (i <= src_size)
			*(dest + i) = *(src + i);
		else
			*(dest + i) = '\0';
		i ++;
	}
	return (dest);
}
