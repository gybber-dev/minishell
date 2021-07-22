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

void	handle_sigquit(int sig)
{
//	printf("in_Sigquit\n");
	if (sig == SIGQUIT)
	{
//		printf("Sigquit\n");
//		if (g_data.is_fork == 1)
//		{
			printf("Quit (core dumped)\n");
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


int			iterable_init(t_all *all)
{
	all->proc.fix_fd.in = 0;
	all->proc.fix_fd.out = 1;
	all->is_pipel = 0;
	std_fd(SAFE_TO, &(all->proc.backup_fd));
}

void check_fd(void)
{
	int fd = dup(0);
	int fd1 = dup(0);
	int fd2 = dup(0);
	int fd3 = dup(0);
	int fd4 = dup(0);
	int fd5 = dup(0);
	int fd6 = dup(0);
	printf("check_fd: %d\n", fd);
	printf("check_fd: %d\n", fd1);
	printf("check_fd: %d\n", fd2);
	printf("check_fd: %d\n", fd3);
	printf("check_fd: %d\n", fd4);
	printf("check_fd: %d\n", fd5);
	printf("check_fd: %d\n", fd6);
	close(fd);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
	close(fd6);
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
//	signal(SIGQUIT, SIG_IGN);
	init_struct(&all, envp);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell: ");
		printf("0: %p\n", line);
		if (!line)
		{
			printf("\033[A\nminishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (*line && !check_valid(line, &all))
		{

			add_history(line);
			iterable_init(&all);
			is_finished = 1;
			while(is_finished)
			{
				signal(SIGINT, handler_sigint);
				is_finished = parser(&line, &all);
//				print_all(&all);
				exec_command(&all);
				clear_cmd(&all);
				printf("status: %d\n", all.vlast);
			}

			std_fd(TAKE_FROM, &(all.proc.backup_fd));
			close(all.proc.backup_fd.in);
			close(all.proc.backup_fd.out);
//			check_fd();
		}
		free(line);
//		signal(SIGQUIT, SIG_IGN);
	}
	return 0;
}
