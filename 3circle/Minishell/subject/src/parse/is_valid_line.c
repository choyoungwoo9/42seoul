/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:24:47 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/29 18:52:47 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int	is_valid_quoto(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
		{
			while (line[++i] != 34)
			{
				if (line[i] == '\0')
					return (0);
			}
		}
		if (line[i] == 39)
		{
			while (line[++i] != 39)
			{
				if (line[i] == '\0')
					return (0);
			}
		}
	}
	return (1);
}

static int	is_valid_pipe(char *line)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			if (flag == 0)
				return (0);
			while (line[++i] == ' ')
				i ++;
			if (line[i] == '\0')
				return (0);
			i --;
		}
		if (line[i] != ' ')
			flag = 1;
		if (line[i] == 34)
			i += get_str_length_by_limiter(line, i, 34);
		if (line[i] == 39)
			i += get_str_length_by_limiter(line, i, 39);
	}
	return (1);
}

static int	redirect_check(char *line, int *i, char ch)
{
	(*i)++;
	if (line[*i] == ch)
		(*i)++;
	while (1)
	{
		if (line[*i] == ' ')
		{
			(*i)++;
			continue ;
		}
		if (line[*i] == '>' || line[*i] == '<'
			|| line[*i] == '|' || line[*i] == '\0')
			return (0);
		else
			break ;
		(*i)++;
	}
	(*i)--;
	return (1);
}

static int	is_valid_redirect(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += get_str_length_by_limiter(line, i, 34);
		if (line[i] == 39)
			i += get_str_length_by_limiter(line, i, 39);
		if (line[i] == '<' || line[i] == '>')
		{
			if (!redirect_check(line, &i, line[i]))
				return (0);
		}
	}
	return (1);
}

int	is_valid_line(char *line)
{
	if (!is_valid_quoto(line))
		return (0);
	if (!is_valid_pipe(line))
		return (0);
	if (!is_valid_redirect(line))
		return (0);
	return (1);
}
