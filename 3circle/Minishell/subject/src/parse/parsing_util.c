/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:52:29 by youngwch          #+#    #+#             */
/*   Updated: 2023/08/13 12:01:07 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

int	get_str_length_by_limiter(char *str, int index, char limiter)
{
	int	length;

	length = 1;
	while (str[index + length] != limiter)
		length ++;
	return (length);
}

char	*triple_join(char *str1, char *str2, char *str3)
{
	char	*tmp_str;
	char	*ret_str;

	tmp_str = ft_strjoin(str1, str2);
	ret_str = ft_strjoin(tmp_str, str3);
	free(str1);
	free(str2);
	free(str3);
	free(tmp_str);
	return (ret_str);
}

char	*make_exit_code(char *str, int index)
{
	char	*left_str;
	char	*middle_str;
	char	*right_str;
	char	*ret_str;

	left_str = ft_substr(str, 0, index);
	middle_str = ft_itoa(g_exit_code);
	right_str = ft_substr(str, index + 2, ft_strlen(str) - index - 2);
	ret_str = triple_join(left_str, middle_str, right_str);
	free(str);
	return (ret_str);
}

int	is_env_var(char *str)
{
	int	i;

	i = -1;
	if (str[++i] != '$')
		return (0);
	while (str[++i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_')
			return (1);
	}
	return (0);
}

int	get_env_var_length(char *str)
{
	int	i;

	i = 2;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
		i ++;
	}
	return (i - 1);
}
