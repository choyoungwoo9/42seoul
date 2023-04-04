/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:40:28 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/29 14:31:58 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int	get_str_length(char const *s, char c)
{
	int	length;

	length = 0;
	while (*(s + length))
	{
		if (*(s + length) == c)
			return (length);
		if(s[length] == 34)
		{
			length ++;
			while(s[length] != 34)
				length ++;
		}
		if(s[length] == 39)
		{
			length ++;
			while(s[length] != 39)
				length ++;
		}
		length ++;
	}
	return (length);
}

static int	count_str(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*(s))
	{
		if (get_str_length(s, c))
		{
			word_count ++;
			s = s + get_str_length(s, c);
		}
		else
			s ++;
	}
	return (word_count);
}

static int	str_alloc_assign_ptr(char **retptr, char const *s, char c)
{
	int	word_count;
	int	tmp;

	word_count = 0;
	while (*s)
	{
		if (get_str_length(s, c))
		{
			*(retptr + word_count)
				= (char *)malloc(get_str_length(s, c) + 1);
			if (*(retptr + word_count) == 0)
				return (word_count);
			tmp = -1;
			while (++ tmp < get_str_length(s, c))
				*(*(retptr + word_count) + tmp) = *(s + tmp);
			*(*(retptr + word_count) + tmp) = '\0';
			s = s + get_str_length(s, c);
			word_count ++;
		}
		else
			s ++;
	}
	return (word_count);
}

char	**pipe_split(char const *s, char c)
{
	int		word_counting;
	char	**retptr;
	int		allocated_ptr_length;

	word_counting = count_str(s, c);
	retptr = (char **)malloc(sizeof(char *) * (word_counting + 1));
	if (retptr == 0)
		return (0);
	*(retptr + word_counting) = 0;
	allocated_ptr_length = str_alloc_assign_ptr(retptr, s, c);
	if (allocated_ptr_length != count_str(s, c))
	{
		while (allocated_ptr_length >= 0)
		{
			free(*(retptr + allocated_ptr_length));
			allocated_ptr_length --;
		}
		free(retptr);
		return (0);
	}
	return (retptr);
}
