#include "../include/main.h"



int execute(t_execution *execution, int default_input_fd, char **envp)
{
	
	execve(execution->cmd, execution->option_ar, envp);
}