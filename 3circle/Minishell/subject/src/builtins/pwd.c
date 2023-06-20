/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:03:55 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/31 13:33:43 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	pwd(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (PATH_MAX + 1));
	if (getcwd(buffer, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}

char	*get_pwd(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (PATH_MAX + 1));
	if (getcwd(buffer, PATH_MAX) == NULL)
		return (NULL);
	return (buffer);
}
