#include<stdio.h>

int main()
{
	int tmp;

	int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	
	for(int i = 0; i < 10; i ++)
	{
		for(int j = 0; j < 9-i; j ++)
		{
			if(ar[j] > ar[j+1])
			{
				tmp = ar[j];
				ar[j] = ar [j + 1];
				ar[j + 1] = tmp;
			}
		}
	}

	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}