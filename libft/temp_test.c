#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"subject/ft_lstnew_bonus.c"
#include"subject/ft_lstadd_front_bonus.c"
#include"subject/ft_lstsize_bonus.c"
#include"subject/ft_lstlast_bonus.c"
#include"subject/ft_lstadd_back_bonus.c"
#include"subject/ft_lstdelone_bonus.c"
#include"subject/ft_lstclear_bonus.c"
#include"subject/ft_lstiter_bonus.c"
#include"subject/ft_lstmap_bonus.c"
#include"subject/libft.h"
#include"subject/ft_atoi.c"

int main()
{
	printf("문제 ::::::::  9223372036854775807\n");
	printf("%d\n", atoi("9223372036854775807"));
	printf("%d\n", ft_atoi("9223372036854775807"));
	printf("문제 ::::::::  9223372036854775899\n");
	printf("%d\n", atoi("9223372036854775899"));
	printf("%d\n", ft_atoi("9223372036854775899"));
	printf("문제 ::::::::  -9223372036854775808\n");
	printf("%d\n", atoi("-9223372036854775808"));
	printf("%d\n", ft_atoi("-9223372036854775808"));
	printf("문제 ::::::::  -9223372036854775899\n");
	printf("%d\n", atoi("-9223372036854775899"));
	printf("%d\n", ft_atoi("-9223372036854775899"));
	printf("문제 ::::::::  -9223372036854775808123\n");
	printf("%d\n", atoi("-9223372036854775808123"));
	printf("%d\n", ft_atoi("-9223372036854775808123"));
	printf("문제 ::::::::  922337203685477580934\n");
	printf("%d\n", atoi("922337203685477580934"));
	printf("%d\n", ft_atoi("922337203685477580934"));
	printf("문제 ::::::::  21474836478\n");
	printf("%d\n", atoi("21474836478"));
	printf("%d\n", ft_atoi("21474836478"));
	printf("문제 ::::::::  2147483647\n");
	printf("%d\n", atoi("2147483647"));
	printf("%d\n", ft_atoi("2147483647"));
	printf("문제 ::::::::  -2147483647\n");
	printf("%d\n", atoi("-2147483647"));
	printf("%d\n", ft_atoi("-2147483647"));
}