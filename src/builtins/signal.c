#include "../includes/minishell.h"

void	signal_handler(int sig_num)
{
	int		stat_loc;

	wait(&stat_loc);
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (sig_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
		}
		g_status = 128 + sig_num;
	}
	else if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
