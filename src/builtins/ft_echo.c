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
	int		tmp;

	flag = 0;
	tmp = check_flag_n(*(command + 1));
	while (tmp == 1)
	{
		tmp = check_flag_n(*(command + 1));
		if (tmp == 1)
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
