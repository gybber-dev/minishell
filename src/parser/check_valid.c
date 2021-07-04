#include "../includes/minishell.h"

int		check_valid(char *line)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;

	while (*line != '\0')
	{
		if (*line == '>')
		{
			ret = 1;
			while (*line++ == ' ')
				if (*line == '>')
					ret = 1;
		}
		line++;
	}
		printf("%c\n", *line);
	return ret;
}