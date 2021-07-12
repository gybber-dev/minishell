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
	int		fd;

	while(reds && *reds)
	{
		if ((*reds)->type == GT)
		{
			if ((fd = open((*reds)->value, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
			dup2(fd, fix_fd->out);
			close(fd);
		}
		if ((*reds)->type == GT2)
		{
			if ((fd = open((*reds)->value, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
			dup2(fd, fix_fd->out);
			close(fd);
		}
		if ((*reds)->type == LOW)
		{
			if ((fd = open((*reds)->value, O_RDONLY, 0666)) == -1)
			{
				perror("bash");
				exit(EXIT_FAILURE);
			}
			dup2(fd, fix_fd->in);
			close(fd);
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
	if (opt == SAFE_TO)
	{
		fd->in = dup(0);
		fd->out = dup(1);
	}
	else if (opt == TAKE_FROM)
	{
		dup2(fd->in, 0);
		dup2(fd->out, 1);
	}
}

void		do_pipel(t_all *all)
{

}


int			builtins(t_all *all)
{
	int		fd[2];
	pid_t	parent;
	int		status;


	int res = check_redirs(all->cmd->reds, &(all->proc.fix_fd));
//	printf("AFTER REDIRS: [%d, %d]\n", all->proc.fix_fd.in, all->proc.fix_fd.out);
	if (!all->is_pipel)
	{
		if (is_builtin(all->cmd->command[0]))
			exec_builtin(all);
		else
		{
			std_fd(TAKE_FROM, &(all->proc.fix_fd));
			exec_binary(all);
			// may be it's necessary to restore fd before all exits inside exec_binary
			std_fd(TAKE_FROM, &(all->proc.backup_fd));
		}
	}
	else
	{
		pipe(fd);
		if ((parent = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (!parent)
		{
//			printf("\tdaughter\n\tcmd:\t'%s'\n", all->cmd->command[0]);
//			printf("\tspec is: %d\n", all->cmd->spec);
//			printf("\tfd is [%d, %d]\n", fd[0], fd[1]);
			// if not last command write result to the pipe
			if (all->cmd->spec)
			{
//				printf("\tchange fd_out:\t'%d' -> '%d'\n", fd[1], all->proc.fix_fd.out);
				dup2(fd[1], all->proc.fix_fd.out);
			}
			close(fd[1]);
			close(fd[0]);
//			execvp(all->cmd->command[0], all->cmd->command);
//			perror("Could not execve");
//			exit(EXIT_FAILURE);
			if (execve(
					find_binary(
							all->cmd->command[0],
							get_value(all->envs, "PATH")),
					all->cmd->command,
					all->envs)	== -1)
			{
				perror("Could not execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (parent)
		{
//			printf("parent\ncmd:\t'%s'\nwait for:\t'%d'\n", all->cmd->command[0], parent);
//			printf("fd is [%d, %d]\n", fd[0], fd[1]);
			close(fd[1]);
//			printf("change fd_in:\t'%d' -> '%d'\n", fd[0], all->proc.fix_fd.in);
			dup2(fd[0], all->proc.fix_fd.in);
			waitpid(parent, &status, 0);
			close(fd[0]);
		}

	}
	return 0;
}

void		my_init_all(t_all *all, char **envp, int iter)
{
	all->is_pipel = 1;
	if (iter == 0)
	{
		all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		all->cmd->command = (char **)malloc(sizeof(char*) * (2 + 1));
		all->cmd->command[0] = ft_strdup("ls");
		all->cmd->command[1] = "-al";
		all->cmd->command[2] = NULL;

		all->cmd->reds = NULL;
		all->cmd->spec = PIPE;

		all->vlast = 0;
		all->vpid = 0;
	}
	else if (iter == 1)
	{
		all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		all->cmd->command = (char **)malloc(sizeof(char*) * (2 + 1));
		all->cmd->command[0] = ft_strdup("grep");
		all->cmd->command[1] = ft_strdup("o");
		all->cmd->command[2] = NULL;

		all->cmd->reds = (t_red **)malloc(sizeof(t_red *) * (1 + 1));
		all->cmd->reds[0] = (t_red *) malloc(sizeof(t_red));
		all->cmd->reds[0]->type = GT;
		all->cmd->reds[0]->value = "222";
		all->cmd->reds[1] = NULL;
		all->cmd->spec = 0;

		all->vlast = 0;
		all->vpid = 0;
	}
	else if (iter == 2)
		all->cmd = NULL;
}

int			check_fd(void)
{
	int	fd = open("_fd_check", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == 3)
	{
		close(fd);
		return 0;
	}
	close(fd);
	return fd;
}

int processor(char *envp[])
{
	t_all all;
	int		i;

	i = 0;
	all.proc.fix_fd.out = 1;
	all.proc.fix_fd.in = 0;
	all.envs = copy_arrays_2x(envp);
	std_fd(SAFE_TO, &(all.proc.backup_fd));
	while (1)
	{
		my_init_all(&all, envp, i);
		if (!all.cmd)
			break;
		builtins(&all);
		clear(&all);
		i++;
	}
	std_fd(TAKE_FROM, &(all.proc.backup_fd));
	close(all.proc.backup_fd.in);
	close(all.proc.backup_fd.out);

////	char *arr[3] = {"ar=2", "b=3", NULL};
////	char *res = get_value(arr, "ar");
//	char *val = get_value(all.envs, "PATH=");
	int fd_check;
	((fd_check = check_fd()) == 0) ? printf("fd is OK\n") : printf("FD LEAK IS DETECTED! %d\n", fd_check);
	return 0;
}

