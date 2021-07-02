#include "../includes/minishell.h"



/**
** @param cmnd - binary name
** @param paths - $PATH value
** @return MALLOCED path to binary "/usr/bin/git"
*/

char			*find_binary(char *cmnd, char *paths)
{
	char		*path;
	char		**arr;
	char		*tmp;
	struct stat	buf;

	path = NULL;
	if (!cmnd || !paths)
		return NULL;
	arr = ft_split(paths, ':');
	tmp = *arr;
	cmnd = ft_strjoin("/", cmnd);
	while(tmp)
	{
		path = ft_strjoin(tmp, cmnd);
		if (stat(path, &buf) == 0)
			break;
		free(path);
		tmp++;
	}
	free(cmnd);
	clear_arr_2x(arr);
	return path;
}

int				execute_external_command(t_all *all)
{
	char		*path;

	path = get_value(all->envs, "PATH");
	path = find_binary(all->command[0], get_value(all->envs, "PATH"));
	free(path);
	return 0;
}
//int			exec_external_programm(char **command)
//{
//    pid_t pid, wpid;
//    int status;
//
//    pid = fork();
//    if (pid == 0) {
//        // Дочерний процесс
//        if (execve(command[0], &command[1]) == -1) {
//            perror("lsh");
//        }
//        exit(EXIT_FAILURE);
//    } else if (pid < 0) {
//        // Ошибка при форкинге
//        perror("lsh");
//    } else {
//        // Родительский процесс
//        do {
//            wpid = waitpid(pid, &status, WUNTRACED);
//        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//    }
//
//    return 1;
//}

int			is_my_command(char *cmd_name)
{
	int		len;

	if (cmd_name == NULL || (len = ft_strlen(cmd_name)) == 0)
		return 0;
	if (!ft_strncmp(cmd_name, "cd", len))
		return 1;
	if (!ft_strncmp(cmd_name, "echo", len))
		return 1;
	if (!ft_strncmp(cmd_name, "pwd", len))
		return 1;
	if (!ft_strncmp(cmd_name, "env", len))
		return 1;
	if (!ft_strncmp(cmd_name, "export", len))
		return 1;
	if (!ft_strncmp(cmd_name, "unset", len))
		return 1;
	if (!ft_strncmp(cmd_name, "exit", len))
		return 1;
	return 0;
}

void		execute_my_command(t_all *all)
{
	printf("my_command");
	return ;
}

int			builtins(t_all *all)
{
	if ((all->command)[0] == NULL)
	{
		printf("IS IT AVAILABLE ERROR??????\n");
		exit(EXIT_FAILURE);
	}
	if (is_my_command((all->command)[0]) == 1)
		execute_my_command(all);
	else
		execute_external_command(all);
	return 0;
}

void		my_init_all(t_all *all, char **envp)
{
	all->command = (char **)malloc(sizeof(char*) * 2 + 1);
	all->command[0] = ft_strdup("echo");
	all->command[1] = ft_strdup("hello");
	all->command[2] = NULL;
	all->specs = 0;
	all->vlast = 0;
	all->vpid = 0;
	all->envs = copy_arrays_2x(envp);
	print_array_2x(all->envs);
}

//int main(int argc, char *argv[], char *envp[])
//{
//	t_all all;
//
//	//	my_init_all(&all, envp);
//	ft_echo("hi");
////	builtins(&all);
//////	char *arr[3] = {"ar=2", "b=3", NULL};
//////	char *res = get_value(arr, "ar");
////	char *val = get_value(all.envs, "PATH=");
//	return 0;
//}



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