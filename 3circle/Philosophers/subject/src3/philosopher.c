/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:34:02 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/09 10:49:11 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
		return (0);
	t_dinner_info info;
	if(set_dinner(&info, argc, argv))
		return (0);
	start_dinner(&info);
	observe_dinner(&info);
}
