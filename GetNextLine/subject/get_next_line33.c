/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line33.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:48:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/24 17:33:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line_utils.c"
#include <stdio.h>
#define BUFFER_SIZE 10

char	*get_next_line(int fd)
{
	static char	*backup_buffer = 0;
	char	*ret_str;
	char	*tmp_str;
	char	*buffer;
	int i;
	int	length;
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		return 0;
	}
	if(backup_buffer == 0)
	{
		backup_buffer = malloc(sizeof(char));
		*backup_buffer = 0;
	}
	while(*(backup_buffer + i) != '\n' && i < *(backup_buffer + i) != '\0')
		i ++;
	if(i != (int)ft_strlen(backup_buffer))
	{
		tmp_str = backup_buffer;
		ret_str = ft_substr(backup_buffer, 0, i + 1);
		backup_buffer = ft_substr(backup_buffer, i + 1, ft_strlen(backup_buffer) - i - 1);
		free(tmp_str);
		return(ret_str);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	while(1)
	{
		i = 0;
		while(i < BUFFER_SIZE + 1)
		{
			*(buffer + i) = 0;
			i ++;
		}
		length = read(fd, buffer, BUFFER_SIZE);
		if(length == -1)
		{
			free(backup_buffer);
			free(buffer);
			return 0;
		}
		if(length == 0)
		{
			free(buffer);
			if(*backup_buffer == 0)
			{
				free(backup_buffer);
				return 0;
			}
			tmp_str = backup_buffer;
			ret_str = ft_strjoin("", backup_buffer);
			backup_buffer = ft_strjoin("", "");
			free(tmp_str);
			return ret_str;
		}
		i = 0;
		while(*(buffer + i) != '\n' && *(buffer + i))
			i ++;
		if(i != (int)ft_strlen(buffer))
		{
			tmp_str = ft_substr(buffer, 0, i + 1);
			ret_str = ft_strjoin(backup_buffer, tmp_str);
			free(tmp_str);
			tmp_str = backup_buffer;
			backup_buffer = ft_substr(backup_buffer, i + 1, ft_strlen(backup_buffer) - i - 1);
			free(tmp_str);
			free(buffer);
			return ret_str;
		}
		tmp_str = backup_buffer;
		backup_buffer = ft_strjoin(backup_buffer, buffer);
		free(backup_buffer);
	}
}

#include<fcntl.h>
int main()
{
	int fd = open("./exam", O_RDONLY);
	char *tmp;
	//close(fd);
	while(1)
	{
		tmp = get_next_line(fd);
		if(tmp == 0)
		{
			//system("leaks a.out");
			//printf("null");
			return 0;
		}
		else
		{
			printf("출력시작---\n%s\n---출력끝\n", tmp);
			//printf("%s", tmp);
			free(tmp);
		}
	}
}