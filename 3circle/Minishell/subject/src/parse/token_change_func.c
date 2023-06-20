/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_change_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:16:42 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/29 20:19:03 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

char	*change_env_var(char *token, int start, int end, char ***envp)
{
	char	*left_str;
	char	*middle_str;
	char	*right_str;
	char	*key;

	left_str = ft_substr(token, 0, start);
	right_str = ft_substr(token, end + 1, ft_strlen(token) - end - 1);
	key = ft_substr(token, start + 1, end - start);
	middle_str = get_env_value(*envp, key);
	if (!middle_str)
		middle_str = "";
	middle_str = strdup(middle_str);
	free(token);
	free(key);
	return (triple_join(left_str, middle_str, right_str));
}

char	*change_single_quote(char *token, int start, int end)
{
	char	*left_str;
	char	*middle_str;
	char	*right_str;

	left_str = ft_substr(token, 0, start);
	middle_str = ft_substr(token, start + 1, end - start - 1);
	right_str = ft_substr(token, end + 1, ft_strlen(token) - end - 1);
	free(token);
	return (triple_join(left_str, middle_str, right_str));
}

char	*change_double_quote(char *token, int *start, int end, char ***envp)
{
	char	*left_str;
	char	*middle_str;
	char	*right_str;
	int		i;

	left_str = ft_substr(token, 0, *start);
	middle_str = ft_substr(token, *start + 1, end - *start - 1);
	right_str = ft_substr(token, end + 1, ft_strlen(token) - end - 1);
	i = -1;
	while (middle_str[++i])
	{
		if (middle_str[i] == '$')
		{			
			if (middle_str[i + 1] == '?')
				middle_str = make_exit_code(middle_str, i);
			else if (is_env_var(middle_str + i))
				middle_str = change_env_var(middle_str, i, i
						+ get_env_var_length(middle_str + i), envp);
			i --;
		}
	}
	*start += (ft_strlen(middle_str) - 1);
	free(token);
	return (triple_join(left_str, middle_str, right_str));
}
