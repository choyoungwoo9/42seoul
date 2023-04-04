// #include "builtins.h"

// t_info	g_info;
// // int main(int argc, char **argv, char **envp)
// // {
// // 	t_info	g_info;

// // 	g_info.envp = envp;
// // 	env(envp);
// // 	pwd();
// // 	// system("leaks a.out");
// // }

// int main(int argc, char **argv, char **envp)
// {
// 	printf("%d\n", argc);
// 	printf("%s\n", argv[0]);
// 	g_info.envp = dptr_dup(envp);
// 	int result = cd("~/Desktop", &g_info.envp);
// 	printf("%d\n", result);
// 	// pwd();
// 	// env(g_info.envp);
// 	// env(g_info.envp);
// 	export("EUI=JIN", &(g_info.envp));
// 	env(g_info.envp);
// 	unset("EUI", g_info.envp);
// 	env(g_info.envp);
// 	char **sample = malloc(sizeof(char *) * 5);
// 	sample[0] = ft_strdup("-1n");
// 	sample[1] = ft_strdup("-1nn");
// 	sample[2] = ft_strdup("HELLo");
// 	sample[3] = ft_strdup("-nn");
// 	sample[4] = NULL;
// 	echo(sample);
// 	system("leaks a.out");
// 	// return (0);
// }