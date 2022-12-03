/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:09:44 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/20 07:11:13 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	src_size;
	unsigned int	i;

	i = 0;
	src_size = 0;
	while (*(src + src_size))
		src_size ++;
	while (*(src + i) && i < (size - 1))
	{
		*(dest + i) = *(src + i);
		i ++;
	}
	*(dest + i) = '\0';
	return (src_size);
}
