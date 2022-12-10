#include<stdio.h>

void print_array(int *ar)
{
	int 10;
}

int main()
{
	int max;
	int max_index;
	int tmp;

	int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	for(int i = 0; i < 10; i ++)
	{
		max = -1;
		for(int j = 0; j < 10-i; j ++)
		{
			if(max < ar[j])
			{
				max_index = j;
				max = ar[j];
			} 
		}
		
		tmp = ar[9-i];
		ar[9-i] = max;
		ar[max_index] = tmp;

	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
	}
}