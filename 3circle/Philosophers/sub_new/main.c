#include "main.h"
#include "make_table.c"
#include "thread_init.c"
#include "dead_check.c"

int main(int argc, char **argv)
{
	t_info info;
	make_table(&info, argc, argv);
	thread_init(&info);
	dead_check(&info);
}