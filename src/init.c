#include "includes/minishell.h"

static void	init_terminal(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
}

void	init_all(t_all *all, char **envp, int argc, char **argv)
{
	all->vlast = 0;
	all->envs = copy_arrays_2x(envp);
	argc = 0;
	argv = NULL;
	g_status = 0;
	init_signals();
	init_terminal();
}
