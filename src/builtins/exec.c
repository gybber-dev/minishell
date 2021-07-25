#include "../includes/minishell.h"

void	exec_binary(t_all *all)
{
	pid_t	parent;
	int		status;

	parent = fork();
	signal(SIGQUIT, signal_handler);
	if (parent == -1)
		all->vlast = (ft_perror("fork", 71));
	else if (!parent && execve(all->cmd->path, \
				all->cmd->command, all->envs) == -1)
	{
		perror("execve");
		exit(127);
	}
	else if (parent)
	{
		if (is_shell(all->cmd->command[0]))
			signal(SIGINT, SIG_IGN);
		waitpid(parent, &status, 0);
		init_signals();
		if (WIFEXITED(status))
			all->vlast = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			all->vlast = 128 + WTERMSIG(status);
	}
}

void	std_fd(int opt, t_fd *fd)
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

/**
** ALLOCATE path to binary. Need to free
** @param cmd
** @param is_my
** @param path may be equal to NULL
** @param env
*/

static void	exec_simple_command(t_all *all)
{
	if (all->cmd->is_builtin)
		exec_builtin(all);
	else
	{
		std_fd(TAKE_FROM, &(all->proc.fix_fd));
		exec_binary(all);
		std_fd(TAKE_FROM, &(all->proc.backup_fd));
	}
}

static void	check_command_path(char *cmd, int *is_my, char **path, char **env)
{
	char	*from;

	if (!ft_strchr(cmd, '/'))
	{
		*is_my = is_builtin(cmd);
		if (!(*is_my))
		{
			from = get_value(env, "PATH");
			*path = find_binary(cmd, from);
			if (!(*path))
				*path = ft_strdup("fsafdasdf");
		}
	}
	else
		*path = ft_strdup(cmd);
}

void	exec_command(t_all *all)
{
	int		status;

	status = check_redirs(all->cmd->reds, &(all->proc.fix_fd), all);
	if (status != EXIT_SUCCESS)
	{
		all->vlast = status;
		return ;
	}
	if (all->cmd->command[0])
	{
		check_command_path(all->cmd->command[0], &(all->cmd->is_builtin), \
			&all->cmd->path, all->envs);
		if (!all->is_pipel)
			exec_simple_command(all);
		else
			exec_piple_command(all);
	}
}
