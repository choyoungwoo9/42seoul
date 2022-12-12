/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad very bad very bad sort_quick.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:09:49 by youngwch          #+#    #+#             */
/*   Updated: 2022/12/12 11:07:55 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

int partition(int *ar, int left, int right)
{
	int pivot = ar[left];
	int i = left + 1;
	int j = right;
	int tmp;

	while(i <= j)
	{
		while(ar[i] < pivot)
		{
			i ++;
		}
		while(ar[j] > pivot)
		{
			j --;
		}
		if(i < j)
		{
			tmp = ar[i];
			ar[i] = ar[j];
			ar[j] = tmp;
		}
		else
			break;
	}
	tmp = ar[i];
	ar[i] = ar[left];
	ar[left] = tmp;
	return j;
}

void quicksort(int *ar, int left, int right)
{
	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("left : %d, right : %d \n", left, right);
	if(left >= right)
		return ;
	int pivot_index = partition(ar, left, right);
	printf("pivot_index : %d\n", pivot_index);
	quicksort(ar, left, pivot_index-1);
	quicksort(ar, pivot_index + 1, right);
}

int main()
{
	int tmp;
	//int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	// for(int i = 0; i < 10; i++)
	// {
	// 	printf("%d, ", ar[i]);
	// }
	quicksort(ar, 0, 9);
	for(int i = 0; i < 10; i++)
	{
		printf("%d, ", ar[i]);
	}
	printf("\n\n");
}