#include "../include/main.h"

void free_execution_ar(t_execution *execution_ar)
{
	for(int i = 0; execution_ar[i].is_terminated == NOT_NULL_STATE; i ++)
	{
		if(execution_ar[i].cmd)
			free(execution_ar[i].cmd);
		for(int j = 0; execution_ar[i].redirect_ar[j].type != NULL_STATE; j ++)
		{
			free(execution_ar[i].redirect_ar[j].file_name);
		}
		free(execution_ar[i].redirect_ar);
		for(int j = 0; execution_ar[i].option_ar[j]; j ++)
			free(execution_ar[i].option_ar[j]);
		free(execution_ar[i].option_ar);
	}
	free(execution_ar);
}
