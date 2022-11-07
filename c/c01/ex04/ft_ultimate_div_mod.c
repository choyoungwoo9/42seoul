/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:32:42 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/03 18:36:04 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	div_res;
	int	mod_res;

	div_res = *a / *b;
	mod_res = *a % *b;
	*a = div_res;
	*b = mod_res;
}
