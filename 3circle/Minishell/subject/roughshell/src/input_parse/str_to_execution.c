#include "../include/main.h"

static void make_execution(t_execution *exe_ptr, char *str_ar)
{
	char **token_ar = make_token(str_ar); //tap 처리 필요, white space redirect 기준으로 split
	categorize_token(exe_ptr, token_ar);
	exe_ptr->is_terminated = NOT_NULL_STATE;
}

static t_execution *make_execution_ar(char** str_ar)
{
	t_execution *ret_ar;
	int i = 0;
	while(str_ar[i])
		i ++;
	ret_ar = malloc(sizeof(t_execution) * (i + 1));
	i = 0;
	while(str_ar[i])
	{
		make_execution(ret_ar + i, str_ar[i]);
		free(str_ar[i]);
		i ++;
	}
	free(str_ar);
	return ret_ar;
}

t_execution *str_to_execution(char *line)
{
	t_execution *execution_ar;

	if(!is_valid_line(line))
		return NULL;
	char **str_ar = pipe_split(line, '|');
	execution_ar = make_execution_ar(str_ar);
	return execution_ar;
}
