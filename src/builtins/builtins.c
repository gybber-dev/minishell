#include "../includes/minishell.h"

int			execute(char **cmd, char *paths)
{
	char	*path;

	path = find_binary(cmd[0], paths);
	return 0;
}

void		clear(t_all *all)
{
	;
}

int			check_redirs(t_red **reds, t_fd *fix_fd)
{
	while(*reds)
	{
		if ((*reds)->type == GT)
			if ((fix_fd->out =
					open((*reds)->value, O_WRONLY | O_CREAT | O_TRUNC, 0666))
					== -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
		if ((*reds)->type == GT2)
			if ((fix_fd->out =
						 open((*reds)->value, O_WRONLY | O_CREAT | O_APPEND,
							  0666)) == -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
		if ((*reds)->type == LOW)
			if ((fix_fd->in =
						 open((*reds)->value, O_RDONLY, 0666))
						 == -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
		reds++;
	}
	return 0;
}

int			is_builtin(char *command)
{
	return 0;
}

int			exec_binary(t_all *all)
{
	pid_t	parent;
	int		status;


	if ((parent = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (!parent)
	{

		if (execve(
				find_binary(
						all->cmd->command[0],
						get_value(all->envs, "PATH")),
				all->cmd->command,
				all->envs)	== -1)
		{
			perror("Could not execve");
		}
	}
	else if (parent)
	{
		waitpid(parent, &status, 0);

	}
	return 0;
}

int			exec_builtin(t_all *all)
{
	return 0;
}

void		std_fd(int opt, t_fd *fd)
{
	if (opt == BACKUP)
	{
		fd->out = dup(1);
		fd->in = dup(0);
	}
	else if (opt == RESTORE)
	{
		dup2(fd->out, 1);
		dup2(fd->in, 0);
	}

}

int			builtins(t_all *all)
{
	int		fd[2];
	t_fd	backup;

	all->proc.backup_fd.out = dup(1);
	all->proc.backup_fd.in = dup(0);
	std_fd(BACKUP, &(all->proc.backup_fd));
	int res = check_redirs(all->cmd->reds, &(all->proc.fix_fd));
	//
	if (!all->is_pipel)
	{
		if (is_builtin(all->cmd->command[0]))
			exec_builtin(all);
		else
		{
			dup2(all->proc.fix_fd.out, 1);
			dup2(all->proc.fix_fd.in, 0);
			exec_binary(all);
			std_fd(RESTORE, &(all->proc.backup_fd));
		}
	}
	close(backup.in);
	close(backup.out);
	return 0;
}

void		my_init_all(t_all *all, char **envp, int iter)
{
	all->is_pipel = 0;
	if (iter == 0)
	{
		all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		all->cmd->command = (char **)malloc(sizeof(char*) * (1 + 1));
		all->cmd->command[0] = ft_strdup("lss");
		all->cmd->command[1] = NULL;

		all->cmd->reds = (t_red **)malloc(sizeof(t_red *) * (1 + 1));
		all->cmd->reds[0] = (t_red *) malloc(sizeof(t_red));
		all->cmd->reds[0]->type = GT;
		all->cmd->reds[0]->value = "111";
		all->cmd->reds[1] = NULL;
		all->cmd->spec = 0;

		all->vlast = 0;
		all->vpid = 0;
		all->envs = copy_arrays_2x(envp);
		print_array_2x(all->envs);
	}
	else if (iter == 1)
	{
		all->cmd = NULL;
	}
}

//int main(int argc, char *argv[], char *envp[])
//{
//	t_all all;
//	int		i;
//
//	i = 0;
//	all.proc.fix_fd.out = 1;
//	all.proc.fix_fd.in = 0;
//	while (1)
//	{
//		my_init_all(&all, envp, i);
//		if (!all.cmd)
//			break;
//		builtins(&all);
//		clear(&all);
//		i++;
//	}
//////	char *arr[3] = {"ar=2", "b=3", NULL};
//////	char *res = get_value(arr, "ar");
////	char *val = get_value(all.envs, "PATH=");
//	return 0;
//}
