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

int			wait_signal(int sign)
{
	printf("kill %d\n", sign);
//	if (sign == SIGINT)
//	{
//		write(1, "\n", 1);
//		rl_on_new_line();
//		rl_replace_line("", 0);
//		rl_redisplay();
//		exit(EXIT_SUCCESS);
//	}
}


int			main(int argc, char** argv, char **envp)
{
	char	*line;
	t_all	all;
	int		parse_status;

	signal(SIGTERM, SIG_IGN);
	init_struct(&all, envp);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("\033[Aminishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line)
		{
			add_history(line);
			parse_status = 0;
			while(!parse_status )
			{
				parse_status = parser(line, &all);
				if (parse_status == -1)
					break;
				processor(&all);
			}
			if (!ft_strncmp(line, "exit", 4))
				exit(EXIT_SUCCESS);
			free(line);
		}
	}
	return 0;
}
