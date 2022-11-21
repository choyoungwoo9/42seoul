/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:24:35 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/21 10:50:40 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdlib.h>
# include<unistd.h>
# include"libft/libft.h"

int		ft_printf(const char *format, ...);
int		reculsive_write_hexnbr(unsigned long long num, int length);
int		put_hexnbr(unsigned long long tmp);
int		reculsive_write_large_hexnbr(unsigned long long num, int length);
int		put_large_hexnbr(unsigned long long tmp);
void	reculsive_put_unsigned_nbr(unsigned int n, int fd);
void	ft_put_unsigned_nbr_fd(unsigned int n, int fd);
int		find_int_digit(int nbr);
int		find_unsigned_int_digit(unsigned int nbr);
#endif