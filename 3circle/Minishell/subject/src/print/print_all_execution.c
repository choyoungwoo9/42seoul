#include "../include/main.h"

void print_all_execution(t_execution *execution_ar)
{
	for(int i = 0; execution_ar[i].is_terminated == NOT_NULL_STATE; i++)
	{
		printf("argv\n");
		for(int j = 0; execution_ar[i].exev_argv[j]; j++)
		{
			printf("||%s||\n", execution_ar[i].exev_argv[j]);
		}
		printf("redirect_ar\n");
		for(int j = 0; execution_ar[i].redirect_ar[j].type != NULL_STATE; j++)
		{
			printf("%d : ", execution_ar[i].redirect_ar[j].type);
			printf("||%s||\n", execution_ar[i].redirect_ar[j].file_name);
		}
	}
}
