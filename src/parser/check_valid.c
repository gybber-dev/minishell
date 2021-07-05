#include "../includes/minishell.h"

int		check_valid(char *line)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;

	while (*line != '\0')
	{
		if (!ft_strncmp(line, ">", 1) || !ft_strncmp(line, "|", 1) || (!ft_strncmp(line, ">>", 2) && *line++ != '\0'))
		{
			ret = 1;
			line++;
			while (*line == ' ')
				line++;
			if (ft_strncmp(line, ">", 1))
				ret = 0;
		}
		line++;
	}
	return ret;
}