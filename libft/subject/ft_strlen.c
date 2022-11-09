/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:04:52 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/07 17:05:22 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"stdlib.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*(s + length) != 0)
		length ++;
	return (length);
}
