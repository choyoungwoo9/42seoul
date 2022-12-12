#include<stdio.h>

int b = 0;

int main()
{
	char a[] = "aa";
	char c[3];
	
	printf("%p\n", a);
	printf("%p\n", &b);
	*a = 'c';
	b = 2;
	printf("%s\n", a + 3);
	c[3] = 'd';
}