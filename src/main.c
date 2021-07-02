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

int			wait_signal(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(EXIT_SUCCESS);
	}
}


int			main(int argc, char** argv, char **envp)
{
	char	*line;
	t_all	all;
	int		is_finished;
	struct termios term;

	tcgetattr(0, &term);
	term.c_cflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, wait_signal);


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
