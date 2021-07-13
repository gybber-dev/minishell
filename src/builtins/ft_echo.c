#include "../includes/minishell.h"

int			check_flag_n(char *command_1)
{
	if (command_1 && (*command_1 == '-') && (*(++command_1) == 'n'))
	{
		while(*command_1)
		{
			if (*command_1 != 'n')
				return 0;
			command_1++;
		}
		return 1;
	}
	return 0;
}

void		ft_echo(char **command)
{
	char	*tmp;
	int		flag_n;

	if ((flag_n = check_flag_n(*(command + 1))) == 1)
		command++;
	while(*(++command))
	{
		printf("%s", *command);
		if (*(command + 1))
			printf(" ");
	}
	if (!flag_n)
		printf("\n");
}