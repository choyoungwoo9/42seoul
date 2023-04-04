#include "../include/main.h"

void print_all_execution(t_execution *execution_ar)
{
	for(int i = 0; execution_ar[i].is_terminated == NOT_NULL_STATE; i++)
	{
		if(execution_ar[i].cmd)
		printf("cmd : ||%s||\n", execution_ar[i].cmd);
		printf("redirect_ar\n");
		for(int j = 0; execution_ar[i].redirect_ar[j].type != NULL_STATE; j++)
		{
			printf("%d : ", execution_ar[i].redirect_ar[j].type);
			printf("||%s||\n", execution_ar[i].redirect_ar[j].file_name);
		}
		printf("option_ar\n");
		for(int j = 0; execution_ar[i].option_ar[j]; j++)
		{
			printf("||%s||\n", execution_ar[i].option_ar[j]);
		}
	}
}
