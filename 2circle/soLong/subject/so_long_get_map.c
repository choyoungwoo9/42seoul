/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_get_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:57:13 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/23 17:33:21 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_file(int fd, t_game_data *game_data)
{
	char	*one_line_map;
	char	*tmp;
	char	*line;

	one_line_map = malloc(sizeof(char));
	*one_line_map = '\0';
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = one_line_map;
		one_line_map = ft_strjoin(one_line_map, line);
		free(tmp);
		free(line);
	}
	game_data->maps = ft_split(one_line_map, '\n');
	free(one_line_map);
}

void	ber_name_check(char *arg)
{
	int	i;

	i = ft_strlen(arg);
	if (i < 4)
		print_error_exit("FILE_MUST_MIN_.BER");
	if (*(arg - i -1) == 'r')
		print_error_exit("FILE_MUST_MIN_.BER");
	if (*(arg - i -2) == 'e')
		print_error_exit("FILE_MUST_MIN_.BER");
	if (*(arg - i -3) == 'b')
		print_error_exit("FILE_MUST_MIN_.BER");
	if (*(arg - i -4) == '.')
		print_error_exit("FILE_MUST_MIN_.BER");
}

void	get_map(t_game_data *game_data, char *arg)
{
	int		fd;
	char	*map_path;

	ber_name_check(arg);
	map_path = ft_strjoin("./maps/", arg);
	fd = open(map_path, O_RDONLY);
	free(map_path);
	game_data->maps = 0;
	if (fd == -1)
		print_error_exit("NOT_VALID_FILE_PATH");
	read_file(fd, game_data);
}
