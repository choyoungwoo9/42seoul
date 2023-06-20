/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:58:28 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 10:05:31 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static void	make_execution(t_execution *exe_ptr, char *str_ar, char ***envp)
{
	char	**token_ar;

	token_ar = make_token(str_ar);
	categorize_token(exe_ptr, token_ar, envp);
	exe_ptr->is_terminated = NOT_NULL_STATE;
}

static t_execution	*make_execution_ar(char **str_ar, char ***envp)
{
	t_execution	*ret_ar;
	int			i;

	i = 0;
	while (str_ar[i])
		i ++;
	ret_ar = malloc(sizeof(t_execution) * (i + 1));
	ret_ar[i].is_terminated = NULL_STATE;
	i = 0;
	while (str_ar[i])
	{
		make_execution(ret_ar + i, str_ar[i], envp);
		free(str_ar[i]);
		i ++;
	}
	free(str_ar);
	return (ret_ar);
}

t_execution	*str_to_execution(char *line, char ***envp)
{
	t_execution	*execution_ar;
	char		**str_ar;

	str_ar = pipe_split(line, '|');
	execution_ar = make_execution_ar(str_ar, envp);
	return (execution_ar);
}
