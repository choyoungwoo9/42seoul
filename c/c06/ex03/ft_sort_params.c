/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:08:59 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/10 12:47:57 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	compare_by_ascii(char *stri, char *strj)
{
	int				index;
	unsigned char	*u_stri;
	unsigned char	*u_strj;

	index = 0;
	u_stri = (unsigned char *)stri;
	u_strj = (unsigned char *)strj;
	while (*(u_stri + index) || *(u_strj + index))
	{
		if (*(u_stri + index) < *(u_strj + index))
			return (0);
		else if (*(u_stri + index) > *(u_strj + index))
			return (1);
		else
			index ++;
	}
	if (*(u_stri + index) < *(u_strj + index))
		return (0);
	else if (*(u_stri + index) > *(u_strj + index))
		return (1);
	else
		index ++;
	return (1);
}

char	**sort_array(int argc, char **argv)
{
	int		i;
	int		j;
	char	*tmp_ch_pointer;

	i = 0;
	while (i < argc - 1)
	{
		j = i + 1;
		while (j < argc)
		{
			if (compare_by_ascii(*(argv + i), *(argv + j)))
			{
				tmp_ch_pointer = argv[i];
				argv[i] = argv[j];
				argv[j] = tmp_ch_pointer;
			}
			j ++;
		}
		i ++;
	}
	return (argv);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 2)
		return (0);
	sort_array(argc - 1, argv + 1);
	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (*(*(argv + i) + j))
		{
			write(1, *(argv + i) + j, 1);
			j ++;
		}
		i ++;
		write(1, "\n", 1);
	}
}
