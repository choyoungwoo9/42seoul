/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:02:58 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/23 13:39:37 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include"get_next_line_utils.c"
#include<stdio.h>
#define USED_BUFFER -5
#define UNUSED_BUFFER -4
#define BUFFER_SIZE 4

int g_index = 0;

void show_all_list(t_list *new_list)
{
	while(new_list)
	{
		printf("**** list print  ****\n");
		printf("content : %s\n", new_list->content);
		printf("length : %d\n", new_list->length);
		printf("state : %d\n", new_list->state_index);
		new_list = new_list->next;
	}
}

void	add_list(t_list **list_start, char *buffer, int length)
{
	t_list	*new_list;
	t_list	*tmp_list;
	new_list = (t_list *)malloc(sizeof(t_list));
	new_list->length = length;
	new_list->state_index = UNUSED_BUFFER;
	new_list->next = NULL;
	new_list->content = malloc(length + 1);
	*((new_list->content) + length) = '\0';
	while(--length >= 0)
	{
		*((new_list->content) + length) = *(buffer + length);
	}
	if (*list_start == 0)
	{
		*list_start = new_list;
	}
	else
	{
		tmp_list = *list_start;
		while (tmp_list->next != 0)
			tmp_list = tmp_list->next;
		tmp_list->next = new_list;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list_start = 0;
	char	*buffer;
	int		length;
	t_list	*tmp_list;
	int		tmp_int;
	char	*ret_ptr;
	char	*tmp_ptr;
	
	ret_ptr = "";
	buffer = (char *)malloc(BUFFER_SIZE);
	while(1)
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if(length == 0)
			return NULL;
		add_list(&list_start, buffer, length);
		printf("******************start********************\n\n");
		printf("g_index : %d\n", g_index);
		g_index ++;
		show_all_list(list_start);
		printf("******************end*******************\n\n");
		tmp_int = 0;
		while (*(buffer + tmp_int) != '\n' && tmp_int != length)
			tmp_int ++;
		printf("newline_check tmp : %d, length : %d\n", tmp_int, length);
		if(tmp_int != length) //개행문자 버퍼에 있음
		{
			tmp_list = list_start;
			while(tmp_list)
			{
				printf("UNUSED_CHECK : %d\n", tmp_list->state_index);
				if(tmp_list->state_index == USED_BUFFER)
					tmp_list = tmp_list->next;
				else
					break;
			}
			if(tmp_list->state_index != UNUSED_BUFFER)
			{
				// printf("ret_ptr : %s + content_ptr : %s\n", ret_ptr, tmp_list->content + tmp_list->state_index + 1);
				ret_ptr = ft_strjoin(ret_ptr, tmp_list->content + tmp_list->state_index + 1);
				tmp_list->state_index = USED_BUFFER;
				tmp_list = tmp_list->next;
			}
			while(tmp_list->next)
			{
				//printf("ret_ptr : %s + tmp_list->content : %s\n", ret_ptr, tmp_list->content);
				ret_ptr = ft_strjoin(ret_ptr, tmp_list->content);
				tmp_list->state_index = USED_BUFFER;
				tmp_list = tmp_list->next;
			}
			tmp_ptr = ft_substr(tmp_list->content, 0, tmp_int);
			printf("state_index : %d\n", tmp_list->state_index);
			printf("tmp_ptr : %s\n", tmp_ptr);
			ret_ptr = ft_strjoin(ret_ptr, tmp_ptr);
			tmp_list->state_index = tmp_int;
			break;
		}
	}
	return (ret_ptr);
}

//file : 012\n3456
#include<fcntl.h>
int main()
{
	printf("********************************BUFFER : %d*************************************\n", BUFFER_SIZE);
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