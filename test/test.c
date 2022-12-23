// #include<stdio.h>
// #include<stdlib.h>
// int main(int argc, char **argv)
// {
// 	static	void *tptr1;
// 	static	void *tptr2;
// 	static	void *tptr3;
// 	static	void *tptr4;
// 	void	*ptr1 = malloc(1);
// 	void	*ptr2 = malloc(1);
// 	void	*ptr3 = malloc(1);
// 	void	*ptr4 = malloc(1);
// 	char	sptr1[10];
// 	char	sptr2[10];
// 	char	sptr3[10];
// 	char	sptr4[10];

// 	printf("%p\n%p\n%p\n%p\n\n", &argc, &argc, &argv, argv);
// 	printf("%p\n%p\n%p\n%p\n\n", &tptr1, &tptr2, &tptr3, &tptr4);
// 	printf("%p\n%p\n%p\n%p\n\n", &ptr1, &ptr2, &ptr3, &ptr4);
// 	printf("%p\n%p\n%p\n%p\n\n", &sptr1, &sptr2, &sptr3, &sptr4);
// 	printf("%p\n%p\n%p\n%p\n\n", ptr1, ptr2, ptr3, ptr4);
// 	printf("%p\n%p\n%p\n%p\n\n", sptr1, sptr2, sptr3, sptr4);
// 	printf("%p\n", (void *)-1);
// }

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	char *errmsg;
	int i;
	FILE* pFile;
	pFile = fopen("unexist.ent", "rb");
	// if (pFile == NULL)
	// 	perror("The following error occurred");
    // printf("== Error Message List ==\n");
    // for(i=0;i<45;i++)
    // {
    //     errmsg = strerror(i);//에러 메시지 확인
	// 	perror(errmsg);
        //printf("<%d>:%s\n",i,errmsg);//에러 번호와 에러 메시지 출력
    //}
}