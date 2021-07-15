#include "../includes/minishell.h"

int			ft_env(char **command, char **env)
{

	if (*(command + 1))
		exit(EXIT_FAILURE);
	while (*env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
}
