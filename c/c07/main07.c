/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main05.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:27:22 by seojyang          #+#    #+#             */
/*   Updated: 2022/10/18 06:55:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ex00/ft_strdup.c"
#include "ex01/ft_range.c"
#include "ex02/ft_ultimate_range.c"
#include "ex03/ft_strjoin.c"
#include "ex04/ft_convert_base.c"
#include "ex04/ft_convert_base2.c"
#include "ex05/ft_split.c"

int	main ()
{	
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("\n--ex00--\n\n");

	printf("%s\n", ft_strdup("hi~"));
	
	printf("\n--ex01--\n\n");

	int i;
	int	min;
	int	max;
	int *arr;

	i = 0;
	min = -6;
	max = 4;
	arr = ft_range(min, max);
	while (min < max)
	{
		printf("%d\n", arr[i++]);
		min++;
	}

	printf("\n--ex02--\n\n");

	int	*arr2;
	int	min2;
	int max2;

	min2 = -6;
	max2 = 5;
	i = 0;
	ft_ultimate_range(&arr2, min2, max2); // &
	while (min2 < max2)
	{
		printf("%d\n", arr2[i++]);
		min2++;
	}

	printf("\n--ex03--\n\n");

	char *strs[4];
	char *sep;

	sep = " : ";
	strs[0] = "I";
	strs[1] = "am";
	strs[2] = "gil";
	strs[3] = "chi";
	printf("size = 2\n");
	printf("%s\n", ft_strjoin(2, strs, sep));
	printf("size = 4\n");
	printf("%s\n", ft_strjoin(4, strs, sep));
	printf("***  Check ABORT! : (( gcc -fsanitize=address *.c ))  ***\n");

	printf("\n--ex04--\n\n");
	
	char *strnum;
	char *base1;
	char *base2;

	strnum = "     ---+--2147483648";
	base1 = "0123456789";
	base2 = "0123456789abcdef";
	printf("%s\n", ft_convert_base(strnum, base1, base2));


	printf("\n--ex05--\n\n");

	int	n = 0;
	char *str = "  I:/ wanttt   one,. ;try";
	char *charset = " :/,.;";
	char **out = ft_split(str, charset);

	while (out[n])
		printf("%s\n", out[n++]);

	printf("\nTESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
	printf("TESTCASE IS NOT GOD\n");
}
