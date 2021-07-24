#include "includes/minishell.h"

void	clear_cmd(t_all *all)
{
	int	i;

	i = -1;
	if (all->cmd->path)
		free(all->cmd->path);
	while (all->cmd->command[++i])
		free_and_return(&(all->cmd->command[i]), 1);
	free(all->cmd->command);
	all->cmd->command = NULL;
	i = -1;
	while (all->cmd->reds[++i])
	{
		free_and_return(&(all->cmd->reds[i]->value), 1);
		free(all->cmd->reds[i]);
		all->cmd->reds[i] = NULL;
	}
	free(all->cmd->reds);
	all->cmd->reds = NULL;
	free(all->cmd);
	all->cmd = NULL;
	unlink(HERE_DOC_FILE);
}

void	iterable_init(t_all *all)
{
	signal(SIGQUIT, signal_handler);
	all->proc.fix_fd.in = 0;
	all->proc.fix_fd.out = 1;
	all->is_pipel = 0;
	std_fd(SAFE_TO, &(all->proc.backup_fd));
	all->is_finished = 1;
}

void	iterable_clear(t_all *all)
{
	std_fd(TAKE_FROM, &(all->proc.backup_fd));
	close(all->proc.backup_fd.in);
	close(all->proc.backup_fd.out);
}

void	getup_exit_code (int from_struct, int is_pipel)
{
	if (g_status == EXIT_SUCCESS && from_struct != EXIT_SUCCESS)
		g_status = from_struct;
	if (is_pipel)
		g_status = from_struct;
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_all			all;

	init_all(&all, envp, argc, argv);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell: ");
		if (!line)
			print_and_exit("\033[Aminishell: exit\n", EXIT_SUCCESS);
		else if (*line && !check_valid(line, &all))
		{
			add_history(line);
			iterable_init(&all);
			while (all.is_finished > 0)
			{
				all.is_finished = parser(&line, &all);
				if (all.is_finished != -1)
					exec_command(&all);
				getup_exit_code(all.vlast, all.is_pipel);
				clear_cmd(&all);
			}
			iterable_clear(&all);
		}
		free(line);
	}
}
