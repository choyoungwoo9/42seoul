#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	static	void *tptr1;
	static	void *tptr2;
	static	void *tptr3;
	static	void *tptr4;
	void	*ptr1 = malloc(1);
	void	*ptr2 = malloc(1);
	void	*ptr3 = malloc(1);
	void	*ptr4 = malloc(1);
	char	sptr1[10];
	char	sptr2[10];
	char	sptr3[10];
	char	sptr4[10];

	printf("%p\n%p\n%p\n%p\n\n", &argc, &argc, &argv, argv);
	printf("%p\n%p\n%p\n%p\n\n", &tptr1, &tptr2, &tptr3, &tptr4);
	printf("%p\n%p\n%p\n%p\n\n", &ptr1, &ptr2, &ptr3, &ptr4);
	printf("%p\n%p\n%p\n%p\n\n", &sptr1, &sptr2, &sptr3, &sptr4);
	printf("%p\n%p\n%p\n%p\n\n", ptr1, ptr2, ptr3, ptr4);
	printf("%p\n%p\n%p\n%p\n\n", sptr1, sptr2, sptr3, sptr4);
	printf("%p\n", (void *)-1);
}