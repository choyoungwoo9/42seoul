#include "../include/main.h"

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    int ret;
    char *line;
	t_execution *execution_ar;
    signal(SIGINT, handler);
    while (1)
    {
        line = readline("r o u ghshell $ ");
        if (line)
        {
			execution_ar = str_to_execution(line);
			add_history(line);
            free(line);
            line = NULL;
			if(execution_ar)
			{
				print_all_execution(execution_ar);
			}
			if(execution_ar)
				free_execution_ar(execution_ar);
			//system("leaks a.out");
        }
        else
        {
            printf("ctrl + d\n");
			exit(0);
        }
    }
    return (0);
}
