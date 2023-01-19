/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_bonus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:13:12 by youngwch          #+#    #+#             */
/*   Updated: 2023/01/15 19:42:23 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_bonus.h"
#include <sys/stat.h>  
#include <fcntl.h>


// void	print_info(t_info info)
// {
// 	printf("%d\n", info.phil_num);
// 	printf("%d\n", info.time_to_die);
// 	printf("%d\n", info.time_to_eat);
// 	printf("%d\n", info.time_to_sleep);
// 	printf("%d\n", info.phil_must_eat);
// }

int main()
{
	t_mysem sem;
	t_info info;
	set_sem(&sem);
	set_info(&info);
	start_dinner(sem, info);
	sleep(5);
	printf("killed_here\n");
	kill(0, SIGINT);
}
