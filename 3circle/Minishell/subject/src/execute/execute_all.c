#include "../include/main.h"

int is_main_process_execute(t_execution *execution_ar)
{
	if(!execution_ar->exev_argv)
		return 0;
	if(is_same_str(execution_ar->exev_argv[0], "cd"))
		return 1;
	if(is_same_str(execution_ar->exev_argv[0], "env"))
		return 1;
	if(is_same_str(execution_ar->exev_argv[0], "export"))
		return 1;
	if(is_same_str(execution_ar->exev_argv[0], "unset"))
		return 1;
	if(is_same_str(execution_ar->exev_argv[0], "pwd"))
		return 1;
	if(is_same_str(execution_ar->exev_argv[0], "exit"))
		return 1;
	return 0;
}

int execute_iterate(t_execution *execution_ar, char ***envp, int **pipe_ar)
{
	int i = -1;
	int p_count = 0;
	int pid;
	while(execution_ar[p_count].is_terminated != NULL_STATE)
		p_count ++;
	if(p_count == 1 && is_main_process_execute(execution_ar))
	{
		return execute(execution_ar, envp, pipe_ar, 0);
	}
	while(++i <= p_count)
	{
		if(i == p_count)
		{		
			int exit_status;
			while (1)
			{
				int status;
				int child_id = wait(&status);
				if(child_id < 0)
					break ;
				if(child_id == pid)
				{
					exit_status = status;
				}
			}
			return exit_status;
		}
		pid = fork();
		if(pid == 0)
			exit(execute(execution_ar+i, envp, pipe_ar, i));
		else
		{
			if(i != 0)
				close(pipe_ar[i-1][0]);
			if(pipe_ar[i] != NULL)
				close(pipe_ar[i][1]);
			
		}
	}
	return 0;
}

void free_pipe(int **pipe_ar)
{
	int i = -1;
	while(pipe_ar[++i])
		free(pipe_ar[i]);
	free(pipe_ar);
}

int change_exit_status(int status)
{
    if (WIFEXITED(status)) {
        return(WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
		int my_signal = WTERMSIG(status);
        return(my_signal + 128);
    }
	else if(WIFSTOPPED(status))
	{
		int my_signal = WSTOPSIG(status);
		return(my_signal + 128);
	}
	return status;
}

int execute_all(t_execution *execution_ar, char ***envp)
{
	int **pipe_ar;
	int p_count = 0;
	while(execution_ar[p_count].is_terminated != NULL_STATE)
		p_count ++;
	if(p_count)
	{
		pipe_ar = malloc(sizeof(int *) * (p_count));
		pipe_ar[p_count - 1] = NULL;	
	}
	else
	{
		pipe_ar = malloc(sizeof(int *) * 1);
		pipe_ar[0] = NULL;
	}
	int i = -1;
	while(++i < p_count - 1)
	{
		pipe_ar[i] = malloc(sizeof(int) * 2);
		pipe(pipe_ar[i]);
	}
	int exit_status = execute_iterate(execution_ar, envp, pipe_ar);
	exit_status = change_exit_status(exit_status);
	free_pipe(pipe_ar);
	return exit_status;
}
