#include "../includes/minishell.h"

static int	open_file_for_single_reds(t_red **reds)
{
	int	fd;

	if ((*reds)->type == GT)
		fd = open((*reds)->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if ((*reds)->type == GT2)
		fd = open((*reds)->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if ((*reds)->type == LOW)
		fd = open((*reds)->value, O_RDONLY, 0666);
	return (fd);
}

int	get_child_status(int status)
{
	int		res;

	res = 0;
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && !res)
		res = 128 + WTERMSIG(status);
	return (res);
}

static int	get_lines_from_input(t_all *all, t_red **reds)
{
	pid_t	parent;
	int		status;

	status = 0;
	parent = fork();
	if (parent == -1)
		all->vlast = 71;
	else if (!parent)
		exec_heredoc((*reds)->value, all);
	else
		waitpid(parent, &status, 0);
	return (get_child_status(status));
}

int	check_redirs(t_red **reds, t_fd *fix_fd, t_all *all)
{
	int		fd;

	while (reds && *reds)
	{
		if ((*reds)->type == GT || (*reds)->type == GT2 || (*reds)->type == LOW)
		{
			fd = open_file_for_single_reds(reds);
			if (fd == -1)
				return (ft_perror("bash", EXIT_FAILURE));
		}
		if ((*reds)->type == LOW2)
		{
			all->vlast = get_lines_from_input(all, reds);
			if (all->vlast != EXIT_SUCCESS)
				return (all->vlast);
			fd = open(HERE_DOC_FILE, O_RDWR, 0666);
		}
		if ((*reds)->type == GT || (*reds)->type == GT2)
			dup2(fd, fix_fd->out);
		if ((*reds)->type == LOW || ((*reds)->type == LOW2))
			dup2(fd, fix_fd->in);
		close(fd);
		reds++;
	}
	return (0);
}
