/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:48:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/23 16:24:37 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include "stdio.h"
#define BUFFER_SIZE 5

char	*get_next_line(int fd)
{
	//이전의 정보를 가지고 있다가, 밀면서 하는 방법
	static char	*backup_buffer = "";
	char	*buffer;
	char	*ret_str;
	char	*tmp_str;
	int i = 0;
	int j = 0;
	while(*(backup_buffer + i) != '\n' && *(backup_buffer + i))
	{
		// printf("h");
		i ++;
	}
	if(i != ft_strlen(backup_buffer))
	{
		ret_str = ft_substr(backup_buffer, 0, i + 1);
		backup_buffer = ft_substr(backup_buffer, i + 1, ft_strlen(backup_buffer) - i - 1);
		return ret_str;
	}
	buffer = malloc(BUFFER_SIZE + 1);
	*(buffer + BUFFER_SIZE) = '\0';
	while(1)
	{
		int check = read(fd, buffer, BUFFER_SIZE);
		if(check == 0)
		{
			return NULL;
		}
		j = 0;
		while(*(backup_buffer + j) != '\n' && j < check)
		{
			j ++;
		}
		if(j != check)
		{
			tmp_str = ft_substr(buffer, 0, j + 1);
			ret_str = ft_strjoin(backup_buffer, tmp_str);
			backup_buffer = ft_substr(tmp_str, j + 1, check - j - 1);
			return ret_str;
		}
		backup_buffer = ft_strjoin(backup_buffer, buffer);
	}
	return ret_str;
}

#include<fcntl.h>
int main()
{
	int fd = open("./exam", O_RDONLY);
	char *tmp;
	while(1)
	{
		tmp = get_next_line(fd);
		if(tmp == 0)
			return 0;
		else
		{
			printf("출력시작---\n%s\n---출력끝\n", tmp);
		}
	}
}