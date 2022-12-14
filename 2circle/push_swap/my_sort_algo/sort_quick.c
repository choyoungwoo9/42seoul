/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_quick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:09:49 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/13 6:39:26 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

int	partition(int *ar, int start, int end)
{
	int pivot = ar[start];
	int left = start + 1;
	int right = end;
	int flag = 0;

	while(left < right)
	{
		while(left < right && ar[left] < pivot)
			left ++;
		while(left < right && ar[right] > pivot)
			right --;
		flag ++;
		printf("left : %d, right : %d start : %d\n", left, right, start);
		for(int i = 0; i < 7; i++)
		{
			printf("%d, ", ar[i]);
		}
		printf("\n");
		int tmp = ar[right];
		ar[right] = ar[left];
		ar[left] = tmp;
	}
	if(flag == 1 && left == start + 1)
		return start;
	if(ar[left] > ar[start])
		left --;
	int tmp = ar[start];
	ar[start] = ar[left];
	ar[left] = tmp;
	return left;
}

void quicksort(int *ar, int start, int end)
{
	printf("quick_sort ------- start : %d, end : %d\n", start, end);
	int pivot_index;
	if(start >= end)
		return ;
	pivot_index = partition(ar, start, end);

	printf("pivot_index : %d\n", pivot_index);
	for(int i = 0; i < 7; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
	
	quicksort(ar, start, pivot_index - 1);
	
	printf("first : ");
	for(int i = 0; i < 7; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");

	quicksort(ar, pivot_index + 1, end);
	printf("second : ");
	for(int i = 0; i < 7; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}

int main()
{
	int tmp;
	int ar[10] = {313, 232323, -222, 0, -2131, 7111, 32342, -2147483648, -5, 2};
	//int ar[6] = {1, 2, 3, 4, 6, 6, 7, 8, 9, 6};
	// for(int i = 0; i < 6; i++)
	// {
	// 	printf("%d, ", ar[i]);
	// }
	for(int i = 0; i < 7; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
	quicksort(ar, 0, 10);
	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}