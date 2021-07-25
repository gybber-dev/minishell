#include "includes/minishell.h"

static void	init_terminal(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
}

void	check_lvl(char ***env)
{
	char	*lvl;
	char	*new_lvl;
	char	*tmp;
	int		num;

	lvl = NULL;
	new_lvl = NULL;
	lvl = get_value(*env, "SHLVL");
	if (lvl && is_number(lvl) == 1)
	{
		num = ft_atoi(lvl);
		if (num < 0)
			set_value_arr_2x("SHLVL=0", env);
		else
		{
			new_lvl = ft_itoa((1 + num) % 1000);
			tmp = ft_strjoin("SHLVL=", new_lvl);
			set_value_arr_2x(tmp, env);
			free(new_lvl);
			free(tmp);
		}
	}
	else
		set_value_arr_2x("SHLVL=1", env);
}

void	init_all(t_all *all, char **envp, int argc, char **argv)
{
	all->vlast = 0;
	all->envs = copy_arrays_2x(envp);
	argv = NULL;
	g_status = 0;
	check_lvl(&(all->envs));
	init_signals();
	init_terminal();
	argc = 0;
}
