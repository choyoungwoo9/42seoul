#include<stdio.h>

//반으로 나눔
//인덱스 개수가 1개가 될때까지 나눔
//합침
//합칠때 소팅을 하면서 합침
//모든 케이스에서 소팅이 되어있기때문에 만약 한쪽 리스트가 모두 사용되었다면 비교하지않고 나머지 리스트를 삽입함
//모두 합쳐지면 리턴

void merge(int *ar, int left, int right)
{
	int sorted[10];
	int mid;
	mid = (left + right) / 2;

	int i, j, k;

	i = left;
	j = mid + 1;
	k = left;
	while(i <= mid && j <= right)
	{
		if(ar[i] <= ar[j])
		{
			sorted[k] = ar[i];
			i ++;
		}
		else
		{
			sorted[k] = ar[j];
			j ++;
		}
		k ++;
	}
	if(i > mid)
	{
		while(j <= right)
		{
			sorted[k] = ar[j];
			k ++;
			j ++;
		}
	}
	else
	{
		while(i <= mid)
		{
			sorted[k] = ar[i];
			k ++;
			i ++;
		}
	}
	int tmp = left;
	while(tmp <= right)
	{
		ar[tmp] = sorted[tmp];
		tmp ++;
	}
}

void mergesort(int *ar, int left, int right)
{
	int mid;
	if(left == right)
		return;
	mid = (left + right) / 2;
	mergesort(ar, left, mid);
	mergesort(ar, mid + 1, right);
	merge(ar, left, right);
}

int main()
{
	int tmp;

	int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

	mergesort(ar, 0, 9);

	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}

	printf("\n\n");
}