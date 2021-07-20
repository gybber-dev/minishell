#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

void		init_struct(t_all *all, char **envp)
{
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


void		clear_cmd(t_all *all)
{
	int i;

	i = -1;

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
}

void		print_all(t_all *all)
{
	printf("\n================================\n");
	printf("commands:\n");
	if (!(all->cmd->command))
		printf("\t%s\n", NULL);
	else
	{
		print_array_2x(all->cmd->command);
	}
	printf("redirs:\n");
	if (!(all->cmd->reds))
		printf("\t%s\n", NULL);
	else
	{
		int i = 0;
		while(all->cmd->reds[i])
		{
			printf("\t%d. type: %d\n", i, all->cmd->reds[i]->type);
			printf("\t%d.  val: %s\n", i, all->cmd->reds[i]->value);
			i++;
			printf("\t---\n");
		}
		printf("\t%d.  %s\n", i, NULL);
		printf("-----\n");
		printf("is spec  : %d\n", all->cmd->spec);
		printf("is pipe  : %d\n", all->is_pipel);
	}
	printf("\n================================\n");

}


int			iterable_init(t_all *all)
{
	all->proc.fix_fd.in = 0;
	all->proc.fix_fd.out = 1;
	all->is_pipel = 0;
	std_fd(SAFE_TO, &(all->proc.backup_fd));
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
			iterable_init(&all);
			is_finished = 1;
			while(is_finished)
			{
				is_finished = parser(&line, &all);
				print_all(&all);
				exec_command(&all);
				clear_cmd(&all);
				printf("status: %d\n", all.vlast);
			}
			std_fd(TAKE_FROM, &(all.proc.backup_fd));
			close(all.proc.backup_fd.in);
			close(all.proc.backup_fd.out);
			free(line);
		}

	}
	return 0;
}
