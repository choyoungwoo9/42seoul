#include<stdio.h>

int main()
{
	int tmp;

	int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	for(int i = 1; i < 10; i ++)
	{
		int j = i;
		while(j > 0)
		{
			if(ar[j-1] < ar[j]) //잘 정렬되어있다면
				break;
			tmp = ar[j-1];
			ar[j-1] = ar[j];
			ar[j] = tmp;
			j --;
		}
	}

	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}