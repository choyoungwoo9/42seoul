/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_good_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:13 by youngwch          #+#    #+#             */
/*   Updated: 2023/04/02 10:54:45 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

extern int	g_exit_code;

int	handle_single_quote(char **token, int *i)
{
	int	j;

	j = 1;
	while ((*token)[*i + j] != 39)
		j ++;
	*token = change_single_quote(*token, *i, *i + j);
	*i = *i + j - 2;
	if (*i == -1)
		return (0);
	if ((*token)[*i] == '\0')
		return (1);
	return (0);
}

int	handle_double_quote(char **token, int *i, char ***envp)
{
	int	j;

	j = 1;
	while ((*token)[*i + j] != 34)
		j ++;
	*token = change_double_quote(*token, i, *i + j, envp);
	if (*i == -1)
		return (0);
	if ((*token)[*i] == '\0')
		return (1);
	return (0);
}

int	handle_env_var(char **token, int *i, char ***envp)
{
	if ((*token)[*i + 1] == '?')
	{
		*token = make_exit_code(*token, *i);
		(*i)--;
	}
	else if (is_env_var(*token + *i))
	{
		*token = change_env_var(*token, *i, *i
				+ get_env_var_length(*token + *i), envp);
		(*i)--;
	}
	if (*i == -1)
		return (0);
	if ((*token)[*i] == '\0')
		return (1);
	return (0);
}

char	*handle_home_path(char *token, char ***envp)
{
	char	*ret_str;
	char	*tmp_str;

	if (is_same_str(token, "~"))
	{
		free(token);
		return (strdup(get_env_value(*envp, "HOME")));
	}
	else if (ft_strncmp("~/", token, 2) == 0)
	{
		tmp_str = ft_substr(token, 1, ft_strlen(token) - 1);
		ret_str = ft_strjoin(get_env_value(*envp, "HOME"), tmp_str);
		free(tmp_str);
		free(token);
		return (ret_str);
	}
	else
		return (token);
}

char	*token_to_good_token(char *token, char ***envp)
{
	int	i;

	if (!token)
		return (NULL);
	token = handle_home_path(token, envp);
	i = -1;
	while (token[++i])
	{	
		if (token[i] == 39)
		{
			if (handle_single_quote(&token, &i))
				return (token);
		}
		else if (token[i] == 34)
		{
			if (handle_double_quote(&token, &i, envp))
				return (token);
		}
		else if (token[i] == '$')
		{
			if (handle_env_var(&token, &i, envp))
				return (token);
		}
	}
	return (token);
}
