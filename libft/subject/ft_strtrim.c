/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:10:02 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/13 09:39:55 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	is_set(char ch, char const *set)
{
	while (*set)
	{
		if (ch == *set)
			return (1);
		set ++;
	}
	return (0);
}

int	find_retstr_length(char const *s1, char const *set)
{
	int	length;

	length = 0;
	while (*(s1 + length))
		length ++;
	while (*(s1))
	{
		if (is_set(*s1, set))
			length --;
		s1 ++;
	}
	return (length + 1);
}

void	assign_ptr(char *ptr, char const *s1, char const *set)
{
	int	tmp;

	tmp = 0;
	while (*(s1))
	{
		if (!is_set(*s1, set))
		{
			*(ptr + tmp) = *s1;
			tmp ++;
		}
		s1 ++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		retstr_length;
	char	*retptr;

	retstr_length = find_retstr_length(s1, set);
	retptr = (char *)malloc(sizeof(char) * retstr_length);
	if (retptr == 0)
		return (0);
	assign_ptr(retptr, s1, set);
	return (retptr);
}
