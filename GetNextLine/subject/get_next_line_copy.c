/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:42:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/22 17:41:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include<stdio.h>
#define BUFFER_SIZE 2

//리스트에 저장
//리스트 생성, 콘텐츠 생성, 이전리스트와 연결
void	lst_addback(t_list **ptr_start, char *ptr_buffer, int length)
{
	int		i;
	t_list	*ptr_list;
	t_list	*ptr_tmp_list;
	//리스트 생성 후 초깃값 할당
	ptr_list = (t_list *)malloc(sizeof(t_list));
	ptr_list->next = NULL;
	ptr_list->content = malloc(length);
	//아직 안 읽은 상태
	ptr_list->state_index = -1;
	i = 0;
	while (i < length)
	{
		*(ptr_list->content + i) = *(ptr_buffer + i);
		i ++;
	}
	if (*ptr_start == 0)
	{
		*ptr_start = ptr_list;
		return ;
	}
	//시작지점부터 마지막 까지 밀고, 마지막 리스트에 추가
	ptr_tmp_list = *ptr_start;
	while (ptr_tmp_list->next != 0)
	{
		ptr_tmp_list = ptr_tmp_list->next;
	}
	ptr_tmp_list -> next = ptr_list;
}

char	*get_next_line(int fd)
{
	static t_list	**ptr_start = 0;
	char			*ptr_buffer;
	int				open_length;
	t_list			*ptr_temp_list;
	int				new_line_index;
	char			*ptr_ret;
	char 			*tmp;

	if (ptr_start == 0) //처음 시작이라면
	{
		ptr_start = (t_list **)malloc(sizeof(t_list *));
		*ptr_start = 0;
	}
	//버퍼사이즈만큼 할당
	ptr_buffer = malloc(BUFFER_SIZE);
	//초기화 (strjoin 할 것임)
	ptr_ret = "";
	//아래 조건문에 걸리면 사용
	ptr_temp_list = *ptr_start;
	while (1)
	{
		//버퍼크기만큼 읽음
		open_length = read(fd, ptr_buffer, BUFFER_SIZE);
		if (open_length == -1) //파일을 열지 못함
		{
			//free(ptr_buffer);
			//리스트 free필요함
			return (0);
		}
		//리스트에 저장
		//리스트 생성, 콘텐츠 생성, 이전리스트와 연결
		lst_addback(ptr_start, ptr_buffer, open_length);
		//개행문자가 있는지 검사 (추후에 널까지 검사하는것으로 분기 생각중)
		new_line_index = 0;
		while (*(ptr_buffer + new_line_index) != '\n')
			new_line_index ++;
		if (new_line_index < BUFFER_SIZE)//버퍼가 개행을 가지고 있음
		{
			//이미 사용한 리스트 밈
			while (ptr_temp_list->state_index == -2)
			{
				ptr_temp_list = ptr_temp_list->next;
			}
			//처음이 아니라서 이전에 개행 인덱스를 찍어 놓았을 떄
			if (ptr_temp_list->state_index != -1)
			{
				tmp = ft_substr(ptr_temp_list->content, new_line_index + 1, open_length - new_line_index - 1);
				ptr_ret = ft_strjoin(ptr_ret, ptr_temp_list->content);
				//free(tmp);
				ptr_temp_list->state_index = -2;
				ptr_temp_list = ptr_temp_list->next;
			}
			//마지막 인덱스까지 밈
			while (ptr_temp_list->next != NULL)
			{	
				tmp = ptr_ret;
				ptr_ret = ft_strjoin(ptr_ret, ptr_temp_list->content);
				//free(tmp);
				ptr_temp_list = ptr_temp_list->next;
			}
			//다 밀었으니까 strjoin하고 state_index에 널 위치 찍음
				tmp = ft_substr(ptr_temp_list->content, 0, new_line_index - 1);
				ptr_ret = ft_strjoin(ptr_ret, ptr_temp_list->content);
				//free(tmp);
				break ;
		}
		else //버퍼가 개행을 가지고 있지 않음
		{
			if(open_length != BUFFER_SIZE) //파일이 끝남
			{
				//리턴 스트링 만들고 프리
			//이미 사용한 리스트 밈
			while (ptr_temp_list->state_index == -2)
			{
				ptr_temp_list = ptr_temp_list->next;
			}
			//처음이 아니라서 이전에 개행 인덱스를 찍어 놓았을 떄
			if (ptr_temp_list->state_index != -1)
			{
				tmp = ft_substr(ptr_temp_list->content, new_line_index + 1, open_length - new_line_index - 1);
				ptr_ret = ft_strjoin(ptr_ret, ptr_temp_list->content);
				//free(tmp);
				ptr_temp_list->state_index = -2;
				ptr_temp_list = ptr_temp_list->next;
			}
			//마지막 인덱스까지 밈
			while (ptr_temp_list != NULL)
			{	
				tmp = ptr_ret;
				ptr_ret = ft_strjoin(ptr_ret, ptr_temp_list->content);
				//free(tmp);
				ptr_temp_list = ptr_temp_list->next;
			}
			break ;
			}
			//다음 파일을 읽어보자
		}
	}
	return (ptr_ret);
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
			write(1, str, i);
		write(1, "\n", 1);
		free(str);
	}
} 