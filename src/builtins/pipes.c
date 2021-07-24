#include "../includes/minishell.h"

static void	exec_in_daughter(t_all *all)
{
	if (all->cmd->is_builtin)
	{
		exec_builtin(all);
		exit(all->vlast);
	}
	if (execve(all->cmd->path, all->cmd->command, all->envs) == -1)
	{
		perror("Could not execve");
		exit(127);
	}
}

void	exec_piple_command(t_all *all)
{
	int		fd[2];
	pid_t	parent;
	int		status;

	pipe(fd);
	parent = fork();
	if (parent == -1)
		all->vlast = 71;
	else if (!parent)
	{
		if (all->cmd->spec)
			dup2(fd[1], all->proc.fix_fd.out);
		close(fd[1]);
		close(fd[0]);
		exec_in_daughter(all);
	}
	else if (parent > 0)
	{
		close(fd[1]);
		dup2(fd[0], all->proc.fix_fd.in);
		waitpid(parent, &status, 0);
		close(fd[0]);
		all->vlast = get_child_status(status);
	}
}
