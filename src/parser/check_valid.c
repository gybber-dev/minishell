#include "../includes/minishell.h"
int		check_symb(char **line)
{
	int ret;

	ret = 0;

	if (!ft_strncmp(*line, ">>", 2))
		ret = 2;
	else if (!ft_strncmp(*line, "|", 1))
		ret = 1;
	else if (!ft_strncmp(*line, ">", 1))
		ret = 1;
	return ret;
}
int		check_valid(char *line)
{
	int		i;
	int		ret;

	ret = 0;

	while (*line != '\0')
	{
		i = check_symb(&line);
		if (i == 1 || (i == 2 && *line++ != '\0'))
		{
			ret = 1;
			line++;
			while (*line == ' ')
				line++;
			if (*line != '\0' && !check_symb(&line))
				ret = 0;
		}
		line++;
	}
	return ret;
}