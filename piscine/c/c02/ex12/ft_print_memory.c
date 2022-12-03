/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:27:41 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/20 16:51:11 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	print_partial_space(void *addr, unsigned int i, unsigned int size)
{
	unsigned int	j;

	j = 0;
	while (i + j < size)
	{
		if (*(char *)(addr + i + j) < ' ' || *(char *)(addr + i + j) >= 127)
			write(1, ".", 1);
		else
			write(1, addr + i + j, 1);
		j ++;
	}
	write(1, "\n", 1);
}

void	print_all_space(void *addr, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j < 16)
	{
		if (*(char *)(addr + i + j) < ' ' || *(char *)(addr + i + j) >= 127)
			write(1, ".", 1);
		else
			write(1, addr + i + j, 1);
		j ++;
	}
	write(1, "\n", 1);
}

void	print_addr_address(void *addr)
{
	char				addr_ch[16];
	unsigned long long	tmp_addr;
	unsigned int		i;
	char				*hex_array;

	tmp_addr = (long long unsigned) addr;
	i = 0;
	hex_array = "0123456789abcdef";
	while (i < 16)
	{
		addr_ch[15 - i] = hex_array[tmp_addr % 16];
		tmp_addr = tmp_addr / 16;
		i ++;
	}
	write(1, addr_ch, 16);
	write(1, ": ", 2);
}

void	print_hex_ascii(void *addr, int i, unsigned int print_space)
{
	char			*hex_array;
	char			ascii_ar[2];
	unsigned int	j;

	hex_array = "0123456789abcdef";
	j = 0;
	while (j < print_space)
	{
		ascii_ar[0] = hex_array[*(unsigned char *)(addr + i + j) / 16];
		ascii_ar[1] = hex_array[*(unsigned char *)(addr + i + j) % 16];
		write(1, ascii_ar, 2);
		if (j % 2)
			write(1, " ", 1);
		j ++;
	}
	while (j < 16)
	{
		write(1, "  ", 2);
		if (j % 2)
			write(1, " ", 1);
		j ++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
	{
		return (addr);
	}
	while (i + 16 < size)
	{
		print_addr_address(addr + i);
		print_hex_ascii(addr, i, 16);
		print_all_space(addr, i);
		i += 16;
	}
	if (i < size + 1)
	{
		print_addr_address(addr + i);
		print_hex_ascii(addr, i, size - i);
		print_partial_space(addr, i, size);
		i ++;
	}
	return (addr);
}
