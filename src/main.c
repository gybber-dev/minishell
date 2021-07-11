#include "includes/minishell.h"

void		init_struct(t_all *all, char **envp)
{
	all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
	all->cmd->command = (char **)malloc(sizeof(char*) * 2 + 1);
	all->cmd->command[0] = ft_strdup("echo");
	all->cmd->command[1] = ft_strdup("hello");
	all->cmd->command[2] = NULL;
	all->cmd->spec = 0;
	all->cmd->reds = NULL;
	all->vlast = 0;
	all->vpid = 0;
	all->envs = copy_arrays_2x(envp);
}

void		processor(t_all *all)
{
	;
}

int			main(int argc, char** argv, char **envp)
{
	char	*line;
	t_all	all;
	int		is_finished;

	init_struct(&all, envp);
	is_finished = 0;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("\033[A\nminishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line)
		{
			add_history(line);
			while(!is_finished)
			{
				is_finished = parser(line, &all);
				processor(&all);
			}

			if (!ft_strncmp(line, "exit", 4))
				exit(EXIT_SUCCESS);
			free(line);
		}

	}
	return 0;
}
