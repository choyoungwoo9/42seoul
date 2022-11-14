#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"subject/ft_strtrim.c"

int main()
{
	char s1[] = "et";
	printf("%s\n", ft_strtrim(s1, "te"));
}