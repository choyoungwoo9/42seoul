/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reverse_alphabet.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:10:34 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/01 10:58:35 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_print_reverse_alphabet(void)
{
	char	rev_alpha;

	rev_alpha = 'z';
	while (rev_alpha >= 'a')
	{
		write(1, &rev_alpha, 1);
		rev_alpha --;
	}
	return ;
}
