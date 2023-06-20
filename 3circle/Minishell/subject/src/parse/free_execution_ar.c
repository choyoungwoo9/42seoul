/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution_ar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:19:42 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/29 18:21:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_execution_ar(t_execution *execution_ar)
{
	int	i;
	int	j;

	i = -1;
	while (execution_ar[++i].is_terminated == NOT_NULL_STATE)
	{
		j = -1;
		while (execution_ar[i].exev_argv[++j])
			free(execution_ar[i].exev_argv[j]);
		free(execution_ar[i].exev_argv);
		j = -1;
		while (execution_ar[i].redirect_ar[++j].type != NULL_STATE)
			free(execution_ar[i].redirect_ar[j].file_name);
		free(execution_ar[i].redirect_ar);
	}
	free(execution_ar);
}
