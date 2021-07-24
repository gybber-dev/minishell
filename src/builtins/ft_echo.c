#include "../includes/minishell.h"

static int	check_flag_n(char *command_1)
{
	if (command_1 && (*command_1 == '-') && (*(++command_1) == 'n'))
	{
		while (*command_1)
		{
			if (*command_1 != 'n')
				return (0);
			command_1++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **command)
{
	int		flag;

	flag = 0;
	while (check_flag_n(*(command + 1)) == 1)
	{
		flag = 1;
		command++;
	}
	while (*(++command))
	{
		printf("%s", *command);
		if (*(command + 1))
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
