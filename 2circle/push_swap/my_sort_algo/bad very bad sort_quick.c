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
	
	while(left < right)
	{
		while(left < right && ar[left] < pivot)
			left ++;
		while(left < right && ar[right] > pivot)
			right --;
		int tmp = ar[left];
		ar[left] = ar[right];
		ar[right] = tmp;
	}
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

	printf("pivot : %d\n", pivot_index);
	for(int i = 0; i < 6; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
	
	quicksort(ar, start, pivot_index - 1);
	
	printf("first : ");
	for(int i = 0; i < 6; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");

	quicksort(ar, pivot_index + 1, end);
	printf("second : ");
	for(int i = 0; i < 6; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}

int main()
{
	int tmp;
	int ar[6] = {6, 5, 4, 3, 2, 1};
	//int ar[6] = {1, 2, 3, 4, 6, 6, 7, 8, 9, 6};
	// for(int i = 0; i < 6; i++)
	// {
	// 	printf("%d, ", ar[i]);
	// }
	for(int i = 0; i < 6; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
	quicksort(ar, 0, 6);
	for(int i = 0; i < 6; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}