#include<stdio.h>
#include"printf/subject/ft_printf.c"
#include"printf/subject/libft/ft_putnbr_fd.c"
#include"printf/subject/libft/ft_strlen.c"
#include"printf/subject/printf_util.c"
#include"printf/subject/printf_util2.c"
#include"printf/subject/printf_type.c"
#include<stdarg.h>
// void f(int format, ...)
// {
// 	va_list ap;
// 	va_start(ap, format);
// 	printf("%p\n", ap);
// 	printf("%p\n", (void *)(*ap).overflow_arg_area);
// 	printf("%p\n", (void *)(*ap).reg_save_area);
// 	printf("%i\n", (*ap).fp_offset);
// 	printf("%i\n", (*ap).gp_offset);
// 	char *tmp = va_arg(ap, char *);
// 	printf("%p : %s : %p\n", ap, tmp, tmp);
// 	printf("%p\n", (void *)(*ap).overflow_arg_area);
// 	printf("%p\n", (void *)(*ap).reg_save_area);
// 	printf("%i\n", (*ap).fp_offset);
// 	printf("%i\n", (*ap).gp_offset);
// 	tmp = va_arg(ap, char *);
// 	printf("%p : %s : %p\n", ap, tmp, tmp);
// 	printf("%p\n", (void *)(*ap).overflow_arg_area);
// 	printf("%p\n", (void *)(*ap).reg_save_area);
// 	printf("%i\n", (*ap).fp_offset);
// 	printf("%i\n", (*ap).gp_offset);
// 	int tmp2 = va_arg(ap, int);
// 	printf("%p : %d : %p\n", ap, tmp2, (void *)&tmp2);
// 	printf("%p\n", (void *                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                *)*(*ap).overflow_arg_area);
// 	printf("%p\n", (void *)(*ap).reg_save_area);
// 	printf("%i\n", (*ap).fp_offset);
// 	printf("%i\n", (*ap).gp_offset);
// }

int main()
{
// 	//char *str = "abc";
	int numc = printf("h\t%p}k'jF4z%XJ/Dn$%dLX%xY\v@r", (void *)-7478384456395673757, 1819750100, -863018620, -2379951);
	int numc2 = ft_printf("h\t%p}k'jF4z%XJ/Dn$%dLX%xY\v@r", (void *)-7478384456395673757, 1819750100, -863018620, -2379951);
	printf("printf return : %d\n", numc);
	printf("ft_printf return : %d\n", numc2);
// 	f(1, "abc", "123", 999);
	printf("%s", (char *)0);
}