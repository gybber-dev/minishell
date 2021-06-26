#include "../includes/minishell.h"

int				execute_external_command(t_all *all)
{
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