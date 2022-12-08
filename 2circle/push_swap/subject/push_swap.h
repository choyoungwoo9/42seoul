/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeong-u <joyeong-u@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:59:54 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/08 22:58:14 by joyeong-u        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>

typedef	struct s_stack
{
	int	number;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;
#endif