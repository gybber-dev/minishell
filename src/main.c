#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

void		init_struct(t_all *all, char **envp)
{
//	all->cmd->reds = NULL;
	all->vlast = 0;
	all->vpid = 0;
	all->envs = copy_arrays_2x(envp);
}

void handler_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handler_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		printf("SIGQUIT\n");
	}
}

void	handle_sigquit(int sig)
{
	printf("in_Sigquit\n");
	if (sig == SIGQUIT)
	{
		printf("Sigquit\n");
//		if (g_data.is_fork == 1)
//		{
//			printf("Quit: 3\n");
//			rl_on_new_line();
//			rl_replace_line("", 0);
//		}
//		else
//		{
			rl_on_new_line();
			rl_replace_line("", 0);
//		}
	}
}



void		clear_cmd(t_all *all)
{
	;
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
//	all->cmd->reds = NULL;
	std_fd(SAFE_TO, &(all->proc.backup_fd));
}

int			main(int argc, char** argv, char **envp)
{
	char	*line;
	t_all	all;
	int		is_finished;
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_struct(&all, envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell: ");
		if (!line)
		{
			printf("\033[A\nminishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line)
		{
			signal(SIGQUIT, handle_sigquit);
			add_history(line);
			iterable_init(&all); // TODO Dinar add init here
			is_finished = 1;
			while(is_finished)
			{
				is_finished = parser(&line, &all);
				print_all(&all);
				exec_command(&all);
				clear_cmd(&all); // TODO Dinar clear all here
				printf("status: %d\n", all.vlast);
			}
			std_fd(TAKE_FROM, &(all.proc.backup_fd));
			close(all.proc.backup_fd.in);
			close(all.proc.backup_fd.out);
			free(line);
		}
//		signal(SIGQUIT, SIG_IGN);
	}
	return 0;
}
