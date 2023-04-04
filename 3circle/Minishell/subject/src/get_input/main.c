#include "../include/main.h"

int exit_code;

static void terminal_routine(char *line, char **envp, t_execution	*execution_ar)
{
	if(*line)
		add_history(line);
	if(!is_valid_line(line))
	{
		printf("syntax error\n");
		exit_code = 256 + 2;
		free(line);
		return ;
	}
	execution_ar = str_to_execution(line, &envp);
    free(line);
    line = NULL;
	if(execution_ar)
	{
		//print_all_execution(execution_ar);
		exit_code = execute_all(execution_ar, &envp);
		free_execution_ar(execution_ar);
	}
	//system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
    char		*line;
	t_execution	*execution_ar;
	struct		termios term;

	envp = dptr_dup(envp);
	input_handler(&term);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	exit_code = 0;
    while (1)
    {
		line = readline("bash $ ");
    	if (line)
    	{
			terminal_routine(line, envp, execution_ar);
		}
		else
		{
			print_eof();
			exit(0);
		}
    }
    return (0);
}
