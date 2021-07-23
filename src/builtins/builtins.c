#include "../includes/minishell.h"

int	open_file_for_single_reds(t_red **reds)
{
	int	fd;

	if ((*reds)->type == GT)
		fd = open((*reds)->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if ((*reds)->type == GT2)
		fd = open((*reds)->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if ((*reds)->type == LOW)
		fd = open((*reds)->value, O_RDONLY, 0666);
	return fd;
}

int			get_child_status(int status)
{
	int		res;

	res = 0;
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && !res)
		res = 128 + WTERMSIG(status);
	return (res);
}

int	get_lines_from_input(t_all *all, t_red **reds)
{
	pid_t	parent;
	int		pipe_fd[2];
	int		status;

	if ((parent = fork()) == -1)
		all->vlast = 71;
	else if (!parent)
		exec_heredoc((*reds)->value, all, pipe_fd);
	else if (parent > 0)
	{
		g_pid = 1;
		waitpid(parent, &status, 0);
		return (get_child_status(status));
	}
}



int			check_redirs(t_red **reds, t_fd *fix_fd, t_all *all)
{
	int		fd;
	pid_t	parent;
	int		pipe_fd[2];
	int		status;

	while(reds && *reds)
	{
		if ((*reds)->type == GT || (*reds)->type == GT2 || (*reds)->type == LOW)
		{
			fd = open_file_for_single_reds(reds);
			if (fd == -1)
				return (ft_perror("bash", EXIT_FAILURE));
			if ((*reds)->type == GT || (*reds)->type == GT2)
				dup2(fd, fix_fd->out);
			if ((*reds)->type == LOW)
				dup2(fd, fix_fd->in);
			close(fd);
		}
		if ((*reds)->type == LOW2)
		{
//			all->vlast =  get_lines_from_input(all, reds);
			if ((parent = fork()) == -1)
				all->vlast = 71;
			else if (!parent)
				exec_heredoc((*reds)->value, all, pipe_fd);
			else if (parent > 0)
			{
				g_pid = 1;
				waitpid(parent, &status, 0);
				all->vlast = get_child_status(status);


				if (all->vlast != EXIT_SUCCESS)
					return (all->vlast);
				int fd_hd = open(HERE_DOC_FILE, O_RDWR, 0666);
				dup2(fd_hd, fix_fd->in);
				close(fd_hd);
			}
		}
		reds++;

	}
	return 0;
}

int			is_builtin(char *command)
{
	if (!command)
		return 0;
	return (
		!(
		ft_strncmp(command, "echo", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "cd", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "export", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "unset", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "exit", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "env", (ft_strlen(command) + 1)) &&
		ft_strncmp(command, "pwd", (ft_strlen(command) + 1))
		)
	);
}

int			exec_binary(t_all *all)
{
	pid_t	parent;
	int		status;

	if ((parent = fork()) == -1)
		return (ft_perror("fork", 71));
	else if (!parent)
	{
		if (execve(all->cmd->path, all->cmd->command, all->envs) == -1)
		{
			perror("Could not execve");
			exit(127);
		}
	}
	else if (parent)
	{
		waitpid(parent, &status, 0);
		if (WIFEXITED(status))
			all->vlast = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			all->vlast = 128 + WTERMSIG(status);
	}
}

void		exec_builtin(t_all *all)
{
	if (!ft_strncmp(all->cmd->command[0], "echo", 5))
		all->vlast = ft_echo(all->cmd->command, all->envs);
	else if (!ft_strncmp(all->cmd->command[0], "pwd", 4))
		all->vlast = ft_pwd();
	else if (!ft_strncmp(all->cmd->command[0], "export", 7))
		all->vlast = ft_export(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "unset", 6))
		all->vlast = ft_unset(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "cd", 3))
		all->vlast = ft_cd(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "env", 4))
		all->vlast = ft_env(all->cmd->command, all->envs);
	else if (!ft_strncmp(all->cmd->command[0], "exit", 5))
		ft_exit(all->cmd->command, &(all->vlast));
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

int			exec_in_daughter(t_all *all)
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

int			exec_simple_command(t_all *all)
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

int			exec_piple_command(t_all *all)
{
	int		fd[2];
	pid_t	parent;
	int		status;

	pipe(fd);
	if ((parent = fork()) == -1)
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
		g_pid = 1;
		close(fd[1]);
		dup2(fd[0], all->proc.fix_fd.in);
		waitpid(parent, &status, 0);
		close(fd[0]);
		if (WIFEXITED(status))
			all->vlast = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			all->vlast = 128 + WTERMSIG(status);
	}
}


/**
 * ALLOCATE path to binary. Need to free
 * @param cmd
 * @param is_my
 * @param path may be equal to NULL
 * @param env
 */
void		check_command(char *cmd, int *is_my, char **path, char **env)
{
	char	*from;

	if (!ft_strchr(cmd, '/'))
	{
		*is_my = is_builtin(cmd);
		if (!(*is_my))
		{
			from = get_value(env, "PATH");
			*path = find_binary(cmd, from);
			// for "a.out"
			if (!(*path))
				*path = ft_strdup(cmd);
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
		return;
	}
	if (all->cmd->command[0])
	{
		check_command(all->cmd->command[0], &(all->cmd->is_builtin),
					&all->cmd->path, all->envs);
		if (!all->is_pipel)
			exec_simple_command(all);
		else
			exec_piple_command(all);
	}
	all->vlast = EXIT_SUCCESS;
}