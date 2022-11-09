#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<strings.h>
#include"libft.h"

int main()
{
	printf("******************isalpha_test*********************\n\n");
	char ch1 = 'a';
	char ch2 = ' ';
	char ch3 = 'Z';
	char ch4 = '@';
	printf("case : a Z@ isalpha : %d%d%d%d\n", isalpha(ch1), isalpha(ch2), isalpha(ch3), isalpha(ch4));
	printf("case : a Z@ ft_isalpha : %d%d%d%d\n", ft_isalpha(ch1), ft_isalpha(ch2), ft_isalpha(ch3), ft_isalpha(ch4));
	printf("\n\n******************isdigit_test*********************\n\n");
	ch1 = '0';
	ch2 = '#';
	ch3 = '9';
	ch4 = ' ';
	printf("case : 0#9  isdigit : %d%d%d%d\n", isdigit(ch1), isdigit(ch2), isdigit(ch3), isdigit(ch4));
	printf("case : 0#9  ft_isdigit : %d%d%d%d\n", ft_isdigit(ch1), ft_isdigit(ch2), ft_isdigit(ch3), ft_isdigit(ch4));
	printf("\n\n******************isalnum_test*********************\n\n");
	ch1 = 'Z';
	ch2 = '@';
	ch3 = '9';
	ch4 = 'a';
	printf("case : Z@9a isalnum : %d%d%d%d\n", isalnum(ch1), isalnum(ch2), isalnum(ch3), isalnum(ch4));
	printf("case : Z@9a ft_isalnum : %d%d%d%d\n", ft_isalnum(ch1), ft_isalnum(ch2), ft_isalnum(ch3), ft_isalnum(ch4));
	printf("\n\n******************isascii_test*********************\n\n");
	int num1 = -1;
	int num2 = 0;
	int num3 = 100;
	int num4 = 127;
	int num5 = 128;
	printf("case : -1 0 100 127 128 isascii : %d%d%d%d%d\n", isascii(num1), isascii(num2), isascii(num3), isascii(num4), isascii(num5));
	printf("case : -1 0 100 127 128 ft_isascii : %d%d%d%d%d\n", ft_isascii(num1), ft_isascii(num2), ft_isascii(num3), ft_isascii(num4), ft_isascii(num5));
	printf("\n\n******************isprint_test*********************\n\n");
	ch1 = '@';
	ch2 = '~';
	ch3 = ' ';
	ch4 = '(';
	printf("case : @~ ( isprint : %d%d%d%d\n", isprint(ch1), isprint(ch2), isprint(ch3), isprint(ch4));
	printf("case : @~ ( ft_isprint : %d%d%d%d\n", ft_isprint(ch1), ft_isprint(ch2), ft_isprint(ch3), ft_isprint(ch4));
	printf("\n\n******************strlen_test*********************\n\n");
	char *str1 = "ABCDWEFDSF";
	char *str2 = "";
	printf("strlen : %lu %lu\n", strlen(str1), strlen(str2));
	printf("ft_strlen : %lu %lu\n", ft_strlen(str1), ft_strlen(str2));
	printf("\n\n******************memset_test*********************\n\n");
	str1 = (char *)malloc(sizeof(char) * 6);
	for(int i = 0; i < 6; i ++)
		*(str1 + i) = 9;
	str2 = (char *)malloc(sizeof(char) * 6);
	for(int i = 0; i < 6; i ++)
		*(str2 + i) = 9;
	for(int i = 0; i < 6; i ++)
		printf("%d", *(str1 + i));
	printf("\n");
	memset(str1, 3, 7);
	ft_memset(str2, 3, 7);
	printf("memset");
	for(int i = 0; i < 7; i ++)
		printf("%d", *(str1 + i));
	printf("\n");
	printf("ft_memset");
	for(int i = 0; i < 7; i ++)
		printf("%d", *(str2 + i));
	printf("\n");
	printf("\n\n******************bzero_test*********************\n\n");
	char s1[100] = {7};
	char s2[100] = {7};

	for(int i = 0; i < 10; i ++)
		s1[i] = 7;
	for(int i = 0; i < 10; i ++)
		s2[i] = 7;
	
	bzero(s1, 5);
	ft_bzero((void *)s2, 5);

	for(int i = 0; i < 10; i ++)
		printf("%d", *(s1 + i));
	printf("\n");
	for(int i = 0; i < 10; i ++)
		printf("%d", *(s2 + i));
	printf("\n\n******************memcpy_test*********************\n\n");
	char dst1[100];
	char src1[100];
	char dst2[100];
	char src2[100];
	for(int i = 0; i < 10; i ++)
	{
		dst1[i] = 7;
		dst2[i] = 7;
		src1[i] = 0;
		src2[i] = 0;
	}
	memcpy(dst1, src1, 5);
	ft_memcpy(dst2, src2, 5);
	for(int i = 0; i < 10; i ++)
	{
		printf("%d", dst1[i]);
	}
	printf("\n");
	for(int i = 0; i < 10; i ++)
		printf("%d", dst2[i]);
	printf("\n\n******************memmove_test*********************\n\n");
	char dst3[6];
	char dst4[6];
	*(dst3+5) = 0;
	*(dst4+5) = 0;
	for(int i = 0; i < 5; i ++)
	{
		*(dst3+i) = i+'0';
		*(dst4+i) = i+'0';
	}
	//char *src4 = "56789";
	memmove(dst3+2, dst3, 3);
	ft_memmove(dst4+2, dst4, 3);
	printf("memmove : %s\n", dst3);
	printf("ft_memmove : %s\n", dst4);
	printf("\n\n******************toupper_test*********************\n\n");
	printf("%c", toupper('c'));
	printf("%c\n", ft_toupper('c'));
	printf("%c", toupper('Z'));
	printf("%c\n", ft_toupper('Z'));
	printf("%c", toupper('@'));
	printf("%c\n", ft_toupper('@'));
	printf("\n\n******************tolower_test*********************\n\n");
	printf("%c", tolower('c'));
	printf("%c\n", ft_tolower('c'));
	printf("%c", tolower('Z'));
	printf("%c\n", ft_tolower('Z'));
	printf("%c", tolower('@'));
	printf("%c\n", ft_tolower('@'));
	printf("\n\n******************strchr_test*********************\n\n");
	char *s7 = "abcde";
	printf("%p\n", strchr(s7, 'a'));
	printf("%p\n", ft_strchr(s7, 'a'));
	printf("%p\n", strchr(s7, 'e'));
	printf("%p\n", ft_strchr(s7, 'e'));
	printf("%p\n", strchr(s7, 0));
	printf("%p\n", ft_strchr(s7, 0));
	printf("%p\n", strchr(s7, '@'));
	printf("%p\n", ft_strchr(s7, '@'));
	printf("\n\n******************strrchr_test*********************\n\n");
	char *s8 = "aebcdea";
	printf("%p\n", strrchr(s8, 'a'));
	printf("%p\n", ft_strrchr(s8, 'a'));
	printf("%p\n", strrchr(s8, 'e'));
	printf("%p\n", ft_strrchr(s8, 'e'));
	printf("%p\n", strrchr(s8, 0));
	printf("%p\n", ft_strrchr(s8, 0));
	printf("%p\n", strrchr(s8, '@'));
	printf("%p\n", ft_strrchr(s8, '@'));
	printf("\n\n******************strncmp_test*********************\n\n");
	char *str9 = "abc";
	char *str10 = "abf";
	char *str11 = "abfba";
	char *str12 = "abaaa";
	printf("%d\n", strncmp(str9, str10, 4));
	printf("%d\n", ft_strncmp(str9, str10, 4));
	printf("%d\n", strncmp(str11, str12, 3));
	printf("%d\n", ft_strncmp(str11, str12, 3));
	printf("\n\n******************memchr_test*********************\n\n");
	char *str13 = "abacdae";
	printf("%p\n", memchr(str13, 'a', 7));
	printf("%p\n", ft_memchr(str13, 'a', 7));
	printf("%p\n", memchr(str13, 'b', 7));
	printf("%p\n", ft_memchr(str13, 'b', 7));
	printf("%p\n", memchr(str13, 'e', 7));
	printf("%p\n", ft_memchr(str13, 'e', 7));
	printf("%p\n", memchr(str13, '@', 7));
	printf("%p\n", ft_memchr(str13, '@', 7));
	printf("%p\n", memchr(str13, ' ', 7));
	printf("%p\n", ft_memchr(str13, ' ', 7));
	printf("\n\n******************memcmp_test*********************\n\n");
	char *str14 = "abc";
	char *str15 = "abf";
	char *str16 = "abfaa";
	char *str17 = "abxaa";
	printf("%d\n", memcmp(str14, str15, 0));
	printf("%d\n", ft_memcmp(str14, str15, 0));
	printf("%d\n", memcmp(str16, str17, 6));
	printf("%d\n", ft_memcmp(str16, str17, 6));
	printf("\n\n******************strnstr_test*********************\n\n");
}
