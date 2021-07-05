#include "../includes/minishell.h"

int			execute(char **cmd, char *paths)
{
	char	*path;

	path = find_binary(cmd[0], paths);

	return 0;
}

int			builtins(t_all *all)
{
	// TODO Gybber
	return 0;
}

void		my_init_all(t_all *all, char **envp, int iter)
{
	if (iter == 0)
	{
		all->command = (char **)malloc(sizeof(char*) * 1 + 1);
		all->command[0] = ft_strdup("ls");
		all->command[1] = NULL;
		all->specs = PIPE;
		all->vlast = 0;
		all->vpid = 0;
		all->envs = copy_arrays_2x(envp);
		print_array_2x(all->envs);
		all->proc.is_complex = 1;
		all->proc.is_complex = 1;
	}
	else if (iter == 1)
	{
		all->command = (char **)malloc(sizeof(char*) * 2 + 1);
		all->command[0] = ft_strdup("grep");
		all->command[1] = ft_strdup("goo");
		all->command[2] = NULL;
		all->specs = 0;
		all->vlast = 0;
		all->vpid = 0;
		all->envs = copy_arrays_2x(envp);
		print_array_2x(all->envs);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_all all;
	int		i;

	i = 0;
	while (i < 2)
	{
		my_init_all(&all, envp, i);
		builtins(&all);
		i++;
	}
////	char *arr[3] = {"ar=2", "b=3", NULL};
////	char *res = get_value(arr, "ar");
//	char *val = get_value(all.envs, "PATH=");
	return 0;
}



//int main(int argc, char *argv[], char *envp[])
//{
//    printf("%s\n", envp[0]);
//    char *newargv[] = { NULL, "-la", NULL, NULL };
//    char *newenviron[] = { "HOME=usr/bin", NULL };
//
//    if (argc != 2) {
//        fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
//
//    newargv[0] = argv[1];
//
//    execve(argv[1], newargv, newenviron);
//    perror("execve");   /* execve() returns only on error */
//    exit(EXIT_FAILURE);
//}
