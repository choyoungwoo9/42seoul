/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:38:07 by yuikim            #+#    #+#             */
/*   Updated: 2023/03/28 19:30:43 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../../libft/libft.h"//상대 경로로 표시할 필요 있음
//define
# define HOME 1
# define DEFAULT 0

//builtin
int		env(char **envp);
int		pwd(void);
int		cd(char *path, char ***envp);
char	*get_pwd(void);
int		export(char *arg, char ***envp);
int	unset(char *key, char **envp);
int		echo(char **arg);
void	ms_exit(char **arg, int exit_code);
int		export_no_option(char **envp);

//utils
void	show_error(char *cmd);
char	*get_env_value(char **envp, char *key);
char	*set_env_value(char ***envp, char *key, char *value);
void	free_dptr(char **dptr, int opt);
char	*str_total_join(char **words, char *operator);
int		get_dptr_size(char **dptr);
char	**dptr_dup(char **dptr);
void	append_dptr(char ***dptr, char *statement);
void	set_env_statement(char **env_addr, char *key, char *value);
void	make_env_statement(char ***envp_ptr, char *key, char *value);
void	ft_sort_ascii(char **str_arr, int size);
int	check_builtins(char **args, char ***envp);
int is_same_str(char *str1, char *str2);

//type
typedef struct s_info{
	char	**envp;
}	t_info;

#endif
