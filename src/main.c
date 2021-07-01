#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

void		init_struct(t_all *all, char **envp)
{
	all->command = (char **)malloc(sizeof(char*) * 2 + 1);
	all->command[0] = ft_strdup("echo");
	all->command[1] = ft_strdup("hello");
	all->command[2] = NULL;
	all->specs = 0;
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

	is_finished = 0;
	while (1)
	{
		line = readline("minishell: ");
		if (*line)
			add_history(line);
		init_struct(&all, envp);
		while(!is_finished)
		{
			is_finished = parser(line, &all);
			processor(&all);
		}
		free(line);
		if (ft_strncmp(line, "exit", 4))
            exit(EXIT_SUCCESS);
	}
	return 0;
}
