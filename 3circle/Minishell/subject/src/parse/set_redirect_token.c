/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:58:18 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/29 18:58:21 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int	set_redirect_type(t_redirect *redirect_ptr, char *token)
{
	int	i;

	i = 0;
	if (token[i] == '<')
	{
		if (token[++i] == '<')
		{
			i ++;
			redirect_ptr->type = REDIR_HEREDOC;
			redirect_ptr->temp_file = get_ptr_str(&redirect_ptr->type);
		}
		else
			redirect_ptr->type = REDIR_IN;
	}
	else
	{
		if (token[++i] == '>')
		{
			i ++;
			redirect_ptr->type = REDIR_APPEND;
		}
		else
			redirect_ptr->type = REDIR_OUT;
	}
	return (i);
}

void	set_redirect_token(t_redirect *redirect_ptr, char *token)
{
	int	i;
	int	length;

	i = set_redirect_type(redirect_ptr, token);
	while (token[i] == ' ')
		i ++;
	length = 0;
	while (token[i + length] != ' ' && token[i + length] != '\0')
		length ++;
	redirect_ptr->file_name = malloc(sizeof(char) * (length + 1));
	redirect_ptr->file_name[length] = '\0';
	length = 0;
	while (token[i + length] != ' ' && token[i + length] != '\0')
	{
		redirect_ptr->file_name[length] = token[i + length];
		length ++;
	}
	free(token);
}
