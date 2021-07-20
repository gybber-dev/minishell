#include "../includes/minishell.h"

int			ft_env(char **command, char **env)
{
	if (*(command + 1))
		return (EXIT_FAILURE);
	print_array_2x(env);
	return (EXIT_SUCCESS);
}
