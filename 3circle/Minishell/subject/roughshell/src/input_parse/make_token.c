/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:40:28 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/25 19:46:07 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int check_redirect(char const *s, char c)
{
	int length = 0;
	if(s[length] == c)
	{
		length ++;
		if(s[length] == c)
			length ++;
		while(s[length] == ' ')
			length ++;
		while(s[length] != ' ' && s[length] != '\0' && s[length] != '<' && s[length] != '>')
			length ++;
	}
	return length;
}

static int	get_token_length(char const *s)
{
	int	length;

	length = 0;
	while (*(s + length))
	{
		if(check_redirect(s, '>'))
			return check_redirect(s, '>');
		if(check_redirect(s, '<'))
			return check_redirect(s, '<');
		if (s[length] == ' ' || s[length] == '>' || s[length] == '<')
			return (length);
		if(s[length] == 34) // 34 == "
		{
			length ++;
			while(s[length] != 34)
				length ++;
		}
		if(s[length] == 39) // 39 == '
		{
			length ++;
			while(s[length] != 39)
				length ++;
		}
		length ++;
	}
	return (length);
}

static int	count_token(char const *s)
{
	int	word_count;

	word_count = 0;
	while (*(s))
	{
		if (get_token_length(s))
		{
			word_count ++;
			s = s + get_token_length(s);
		}
		else
			s ++;
	}
	return (word_count);
}

static int	token_alloc_assign_ptr(char **retptr, char const *s)
{
	int	word_count;
	int	tmp;

	word_count = 0;
	while (*s)
	{
		if (get_token_length(s))
		{
			*(retptr + word_count)
				= (char *)malloc(get_token_length(s) + 1);
			if (*(retptr + word_count) == 0)
				return (word_count);
			tmp = -1;
			while (++ tmp < get_token_length(s))
				retptr[word_count][tmp] = s[tmp];
			retptr[word_count][tmp] = '\0';
			s = s + get_token_length(s);
			word_count ++;
		}
		else
			s ++;
	}
	return (word_count);
}

char	**make_token(char const *s)
{
	int		word_counting;
	char	**retptr;
	int		allocated_ptr_length;

	word_counting = count_token(s);
	retptr = (char **)malloc(sizeof(char *) * (word_counting + 1));
	if (retptr == 0)
		return (0);
	*(retptr + word_counting) = 0;
	allocated_ptr_length = token_alloc_assign_ptr(retptr, s);
	if (allocated_ptr_length != count_token(s))
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
