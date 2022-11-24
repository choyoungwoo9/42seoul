/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:48:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/24 17:32:24 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #include "get_next_line_utils.c"
// #include <stdio.h>
// #define BUFFER_SIZE 10

char	*get_next_line(int fd)
{
	//이전의 정보를 가지고 있다가, 밀면서 하는 방법
	static char	*backup_buffer = 0;
	char	*buffer;
	char	*ret_str;
	char	*tmp_str;
	int i = 0;
	if(backup_buffer == 0)
	{
		if(fd < 0 || BUFFER_SIZE <= 0)
		{
			// printf("a");
			//free(backup_buffer);
			//free(backup_buffer);
			return 0;
		}
		backup_buffer = (char *)malloc(1);
		if(!backup_buffer)
			return 0;
		*backup_buffer = '\0';
	}
	//printf("backup_buffer : %s\n", backup_buffer);
	while (*(backup_buffer + i) != '\n' && *(backup_buffer + i))
	{
		i ++;
	}
	if (i != (int)ft_strlen(backup_buffer))
	{
		tmp_str = backup_buffer;
		ret_str = ft_substr(backup_buffer, 0, i + 1);
		backup_buffer = ft_substr(backup_buffer, i + 1, ft_strlen(backup_buffer) - i - 1);
		free(tmp_str);
		return ret_str;
	}
	buffer = malloc(BUFFER_SIZE + 1);
	while(1)
	{
		i = 0;
		while(i < BUFFER_SIZE + 1)
		{
			*(buffer + i) = '\0';
			i ++;
		}
		int check = read(fd, buffer, BUFFER_SIZE);
		// printf("buffer : %s\n", buffer);
		//printf("check : %d\n", check);
		// printf("backup_buffer : %s\n", backup_buffer);
		if(check == -1)
		{
			free(buffer);
			free(backup_buffer);
			return NULL;
		}
		if(check == 0)
		{
			free(buffer);
			if(*backup_buffer != '\0')
			{
				ret_str = ft_strjoin("", backup_buffer);
				free(backup_buffer);
				backup_buffer = ft_strjoin("", "");
				return ret_str;
			}
			free(backup_buffer);
			return NULL;
		}
		i = 0;
		while(*(buffer + i) != '\n' && i < check)
		{
			i ++;
		}
		//printf("check : %d, j : %d\n", check, j);
		if(i != check)
		{
			tmp_str = ft_substr(buffer, 0, i + 1);
			//printf("tmp_str : %s\n", tmp_str);
			ret_str = ft_strjoin(backup_buffer, tmp_str);
			free(tmp_str);
			tmp_str = backup_buffer;
			//printf("ret_str : %s\n", ret_str);
			backup_buffer = ft_substr(buffer, i + 1, check - i - 1);
			free(tmp_str);
			free(buffer);
			//printf("backup_buffer : %s\n", backup_buffer);
			return ret_str;
		}
		tmp_str = backup_buffer;
		backup_buffer = ft_strjoin(backup_buffer, buffer);
		free(tmp_str);
	}
}

// #include<fcntl.h>
// int main()
// {
// 	int fd = open("./exam", O_RDONLY);
// 	char *tmp;
// 	close(fd);
// 	while(1)
// 	{
// 		tmp = get_next_line(fd);
// 		if(tmp == 0)
// 		{
// 			//system("leaks a.out");
// 			printf("null");
// 			return 0;
// 		}
// 		else
// 		{
// 			printf("출력시작---\n%s\n---출력끝\n", tmp);
// 			//printf("%s", tmp);
// 			free(tmp);
// 		}
// 	}
// }