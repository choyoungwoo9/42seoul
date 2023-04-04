/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuikim <yuikim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:50:08 by yuikim            #+#    #+#             */
/*   Updated: 2022/12/23 17:46:02 by yuikim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *input, ...);
int		print_c(va_list ap);
int		print_s(va_list ap);
int		print_p(va_list ap);
int		print_d(va_list ap);
int		print_u(va_list ap);
int		print_x(va_list ap);
int		print_upper_x(va_list ap);
int		ft_find_number_figure(unsigned long long n1,
			unsigned long long base_len);
void	ft_putnbr_fd(int nb, int fd);
int		ft_find_figure(long long n);
void	ft_write_base(unsigned long long num, int count, char *base);
size_t	ft_strlen2(char *s);

#endif