/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:59:37 by youngwch          #+#    #+#             */
/*   Updated: 2023/03/31 13:33:22 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../../libft/libft.h"
# define HOME 1
# define DEFAULT 0
# define BUILTINERROR 123

int		env(char **args, char **envp);
int		pwd(void);
int		cd(char *path, char ***envp);
char	*get_pwd(void);
int		export(char **args, char ***envp);
int		unset(char **args, char **envp);
int		echo(char **arg);
void	ms_exit(char **arg);
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
int		check_builtins(char **args, char ***envp);
int		is_same_str(char *str1, char *str2);
void	print_builtin_error(char *str);

typedef struct s_info{
	char	**envp;
}	t_info;

#endif
