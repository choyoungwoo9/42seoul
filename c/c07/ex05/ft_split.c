/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 14:03:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/18 06:57:51 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	is_word(char *charset, char ch)
{
	int	i;

	i = 0;
	while (*(charset + i))
	{
		if (ch == *(charset + i))
			return (0);
		i ++;
	}
	return (1);
}

int	find_length(char *str, char *charset)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (is_word(charset, *(str + i)))
			i ++;
		else
			return (i);
	}
	return (i);
}

void	assign_ptr(char **ptr, char *str, char *charset)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (find_length(str + i, charset))
		{
			*(*ptr + i) = *(str + i);
			i ++;
		}
		else
		{
			*(*ptr + i) = '\0';
			return ;
		}
	}
	*(*ptr + i) = '\0';
	return ;
}

void	alloc_assign_pointer(char **ptr, char *str, char *charset)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (*(str + i))
	{
		if (find_length(str + i, charset))
		{
			*(ptr + word_count)
				= (char *)malloc(find_length(str + i, charset) + 1);
			assign_ptr(ptr + word_count, str + i, charset);
			word_count ++;
			i = i + find_length(str + i, charset);
		}
		else
			i ++;
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**ptr;
	int		i;
	int		word_count;

	i = 0;
	word_count = 0;
	while (*(str + i))
	{
		if (find_length(str + i, charset))
		{
			word_count ++;
			i = i + find_length(str + i, charset);
		}
		else
			i ++;
	}
	ptr = (char **)malloc(sizeof(char *) * (word_count + 1));
	alloc_assign_pointer(ptr, str, charset);
	*(ptr + word_count) = NULL;
	return (ptr);
}
