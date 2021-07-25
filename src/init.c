#include "includes/minishell.h"

static void	init_terminal(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
}

void	easy_sig_handler(int sig_int)
{
	if (sig_int == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	init_all(t_all *all, char **envp, int argc, char **argv)
{
	all->vlast = 0;
	all->envs = copy_arrays_2x(envp);
	argv = NULL;
	g_status = 0;
	if (argc > 1)
	{
		printf("SIG ON\n");
		init_signals();
	}

	else
	{
		printf("SIG OFF\n");
		signal(SIGINT, easy_sig_handler);
	}
	init_terminal();
	argc = 0;
}
