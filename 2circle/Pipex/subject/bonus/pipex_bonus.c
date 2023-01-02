/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:03:08 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/02 10:32:33 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char** argv, char **envp)
{
	if (argc < 5)
		exit_with_message("few arg\n");
	if (!ft_strncmp("here_doc", *(argv + 1), ft_strlen("here_doc")))
	{
		if (argc != 6)
			exit_with_message("heredoc_must_have_5_arg\n");
		heredoc_process(argv, envp);
	}
	else
		recursive_pipe(NULL, argv, argc - 2, envp);
}
