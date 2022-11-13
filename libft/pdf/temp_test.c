#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include"ft_strjoin.c"
#include"ft_strtrim.c"
#include"ft_split.c"
#include"ft_itoa.c"
#include"ft_striteri.c"

void f(unsigned int n, char *str)
{
	if(*(str) == 'c')
		*(str) = *(str) + 1;
}
int main()
{
	char str[4];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';
	ft_striteri(str, f);
	printf("%s\n", str);
}