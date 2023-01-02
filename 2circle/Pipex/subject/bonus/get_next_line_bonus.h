/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:32:56 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/02 11:51:17 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# define BUFFER_SIZE 42

char	*get_next_line(int fd);
char	*gnl_ft_strjoin(char const *s1, char const *s2);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_ft_strlen(const char *s);
char	*read_nothing_in_buf(char *buf, char **save_b, int check);
char	*length_err_check(char *buf, char **save_b, int length);
#endif
