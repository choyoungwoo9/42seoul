/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:42:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/22 18:42:07 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include<stdio.h>
#define BUFFER_SIZE 5

void	lst_addback(t_list **list_start, char *ptr_buffer, int length)
{
	t_list	*list_alloc;
	t_list	*tmp;
	
	list_alloc = (t_list *)malloc(sizeof(t_list));
	list_alloc->state_index = -1;
	list_alloc->next = 0;
	list_alloc->content = (char *)malloc(sizeof(char) * length + 1);
	*(list_alloc->content + length) = 0;
	while(--length >= 0)
	{
		*(list_alloc->content + length) = *(ptr_buffer + length);
	}
	tmp = *list_start;
	if(tmp == 0)
	{
		*list_start = list_alloc;
		return ;
	}
	while(tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = list_alloc;
}

char	*get_next_line(int fd)
{
	static t_list	**list_start = 0;
	t_list	*list_tmp;
	char	*ptr_return;
	char	*ptr_buffer;
	char	*ptr_tmp;
	int		length;
	int		index_newline;
	
	if (list_start == 0)
	{
		list_start = malloc(sizeof(t_list *));
		*list_start = 0;
	}
	ptr_tmp = 0;
	ptr_buffer = malloc(BUFFER_SIZE);
	while(1)
	{
		length = read(fd, ptr_buffer, BUFFER_SIZE);
		if(length == -1 || length == 0)
		{
			//free 필요
			return 0;
		}
		lst_addback(list_start, ptr_buffer, length);
		index_newline = 0;
		while(*(ptr_buffer + index_newline) != '\n')
			index_newline ++;
		//개행문자 버퍼에 있음
		if(length != index_newline)
		{
			list_tmp = *list_start;
			//이미 사용한 리스트 만났을 떄
			while(list_tmp->state_index == -2)
				list_tmp = list_tmp->next;
			//인덱스 찍어놓은 리스트 만났을 때
			if(list_tmp->state_index != -1)
			{
				ptr_tmp = ft_substr
				(list_tmp->content, list_tmp->state_index + 1, BUFFER_SIZE - list_tmp->state_index - 1);
				ptr_return = ft_strjoin("" , ptr_tmp);
				//free(ptr_tmp);
				list_tmp->state_index = -2;
			}
			while(list_tmp->next)
			{	
				ptr_tmp = ptr_return;
				ptr_return = ft_strjoin(ptr_return, list_tmp->content);
				//free(ptr_tmp);
				list_tmp->state_index = -2;
				list_tmp = list_tmp->next;
			}
			ptr_tmp = ptr_return;
			ptr_return = ft_strjoin(ptr_return, list_tmp->content);
			//free(ptr_tmp);
			list_tmp->state_index = index_newline;
			return ptr_return;
		}
		//파일끝나서 버퍼하고 사이즈 다름
		if(length != BUFFER_SIZE)
		{
			list_tmp = *list_start;
			//이미 사용한 리스트 만났을 떄
			while(list_tmp->state_index == -2)
				list_tmp = list_tmp->next;
			//인덱스 찍어놓은 리스트 만났을 때
			if(list_tmp->state_index != -1)
			{
				ptr_tmp = ft_substr
				(list_tmp->content, list_tmp->state_index + 1, BUFFER_SIZE - list_tmp->state_index - 1);
				ptr_return = ft_strjoin("" , ptr_tmp);
				//free(ptr_tmp);
				list_tmp->state_index = -2;
			}
			while(list_tmp)
			{	
				ptr_tmp = ptr_return;
				ptr_return = ft_strjoin(ptr_return, list_tmp->content);
				//free(ptr_tmp);
				list_tmp->state_index = -2;
				list_tmp = list_tmp->next;
			}
			//free 필요
			return ptr_return;
		}
	}
	return 0;
}

#include<stdio.h>
#include<fcntl.h>
int main()
{
	int fd;
	
	fd = open("./exam", O_RDONLY);
	while(1)
	{
		char *str = get_next_line(fd);
		if(str == NULL)
			break;
		int i = 0;
		while(*(str + i) != '\n')
		{
			write(1, str + i, 1);
			i ++;
		}
		write(1, "\n", 1);
		//free(str);
	}
} 