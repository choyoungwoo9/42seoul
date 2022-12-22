/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:57:13 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/22 09:53:49 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/ft_split.c"

void	get_map(t_game_data *game_data)
{
	int fd;
	char *line;
	char *one_line_map;
	int count = 0;
	char *tmp;
	one_line_map = malloc(sizeof(char));
	*one_line_map = '\0';
	fd = open("./maps/valid_map.ber", O_RDONLY);
	game_data->column = 0;
	game_data->row = 0;
	game_data->maps = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		tmp = one_line_map;
		one_line_map = ft_strjoin(one_line_map, line);
		free(tmp);
		free(line);
		int i = 0;
	};
	game_data->maps = ft_split(one_line_map, '\n');
	free(one_line_map);
}

// int main()
// {
// 	t_game_data game_data;
// 	get_map(&game_data);
// 	int i = 0;
// 	while(*(game_data.maps + i))
// 	{
// 		printf("%s\n", *(game_data.maps + i));
// 		i ++;
// 		printf("i : %d\n", i);
// 	}
// }