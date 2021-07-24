#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"


void sigint_handler(int sig_num)
{
	int stat_loc;

	wait(&stat_loc);
//	write(1, "\n", 1);

//	printf("by signal? : %d\n", WIFSIGNALED(stat_loc));
//	if(WIFSIGNALED(stat_loc))
//	printf("sig: %d\nstat_loc: %d", sig_num, get_child_status(stat_loc));
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (sig_num == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
//		g_mini.status_set = 1;
		g_status = 128 + sig_num;
	}
	else if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
//		if (hd)
//		{
//			kill(hd, SIGINT);
//			hd = 0;
//		}

	}
//	printf("check: %d", g_status);
}

void
init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}



void		init_struct(t_all *all, char **envp)
{
	all->vlast = 0;
	all->envs = copy_arrays_2x(envp);
}

void		clear_cmd(t_all *all)
{
	int i;

	i = -1;

	if (all->cmd->path)		  // may be NULL
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


void	iterable_init(t_all *all)
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
	struct termios term;

	argc = 2;
	argv = NULL;
	g_status = 0;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	init_signals();
	init_struct(&all, envp);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("\033[Aminishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line && !check_valid(line, &all))
		{
			add_history(line);
			iterable_init(&all);
			is_finished = 1;
			while(is_finished > 0)
			{
//				printf("before: %d", all.vlast);
				if ((is_finished = parser(&line, &all)) != -1)
				{

					exec_command(&all);
				}
				if (!g_status)
					g_status = all.vlast;
				clear_cmd(&all);
//				printf("statuasdfasdfadsfs: %d\n", all.vlast);
			}
//			printf("out_stasadfasdfasdfat: %d\n", all.vlast);
//			all.vlast = g_status;
			std_fd(TAKE_FROM, &(all.proc.backup_fd));
			close(all.proc.backup_fd.in);
			close(all.proc.backup_fd.out);
		}
		free(line);
	}
	return 0;
}
