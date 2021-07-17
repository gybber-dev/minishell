#include "../includes/minishell.h"

int			ft_env(char **command, char **env)
{

	if (*(command + 1))
		return (EXIT_FAILURE);
	while (*env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
	return (EXIT_SUCCESS);
}
