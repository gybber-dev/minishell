#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

void		init_struct(t_all *all, char **envp)
{
	all->cmd->reds = NULL;
	all->vlast = 0;
	all->vpid = 0;
	all->envs = copy_arrays_2x(envp);
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


void		processor(t_all *all)
{
	;
}

int			main(int argc, char** argv, char **envp)
{
	char	*line;
	t_all	all;
	int		is_finished;

	signal(SIGTERM, SIG_IGN);
	init_struct(&all, envp);
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
			is_finished = 1;
			while(is_finished)
			{
				is_finished = parser(&line, &all);
				processor(&all);
			}

			if (!ft_strncmp(line, "exit", 4))
				exit(EXIT_SUCCESS);
			free(line);
		}

	}
	return 0;
}
