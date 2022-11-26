/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:48:36 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/26 13:32:32 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_nothing(char *buffer, char **backup_buffer)
{
	char	*ret_str;
	
	free(buffer);
	if(**backup_buffer != '\0')
	{
		ret_str = ft_strjoin("", *backup_buffer);
		free(*backup_buffer);
		*backup_buffer = ft_strjoin("", "");
		return ret_str;
	}
	free(*backup_buffer);
	*backup_buffer = 0;
	return NULL;
}

char	*get_next_line(int fd)
{
	static char	*backup_buffer = 0;
	char	*buffer;
	char	*ret_str;
	char	*tmp_str;
	int		i;
	
	if(backup_buffer == 0)
	{
		backup_buffer = (char *)malloc(1);
		*backup_buffer = '\0';
	}
	i = 0;
	while (*(backup_buffer + i) != '\n' && *(backup_buffer + i))
		i ++;
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
		if(check == -1)
		{
			free(buffer);
			free(backup_buffer);
			backup_buffer = 0;
			return NULL;
		}
		// if(check == 0)
		// {
		// 	free(buffer);
		// 	if(*backup_buffer != '\0')
		// 	{
		// 		ret_str = ft_strjoin("", backup_buffer);
		// 		free(backup_buffer);
		// 		backup_buffer = ft_strjoin("", "");
		// 		return ret_str;
		// 	}
		// 	free(backup_buffer);
		// 	backup_buffer = 0;
		// 	return NULL;
		// }
		i = 0;
		while (*(buffer + i) != '\n' && i < check)
			i ++;
		if (i != check)
		{
			tmp_str = ft_substr(buffer, 0, i + 1);
			ret_str = ft_strjoin(backup_buffer, tmp_str);
			free(tmp_str);
			tmp_str = backup_buffer;
			backup_buffer = ft_substr(buffer, i + 1, check - i - 1);
			free(tmp_str);
			free(buffer);
			return ret_str;
		}
		tmp_str = backup_buffer;
		backup_buffer = ft_strjoin(backup_buffer, buffer);
		free(tmp_str);
	}
}

#include<fcntl.h>
#include<stdio.h>
int main()
{
	int fd = open("./exam", O_RDONLY);
	char *tmp;
	while(1)
	{
		tmp = get_next_line(fd);
		if(tmp == 0)
		{
			//system("leaks a.out");
			printf("null pointer");
			tmp = get_next_line(fd);
			printf("출력시작---\n%s\n---출력끝\n", tmp);
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