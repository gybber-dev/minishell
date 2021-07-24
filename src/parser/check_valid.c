#include "../includes/minishell.h"
int	check_symb(char **line)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(*line, ">>", 2))
		ret = 2;
	else if (!ft_strncmp(*line, "|", 1))
		ret = 1;
	else if (!ft_strncmp(*line, ">", 1))
		ret = 1;
	return (ret);
}

void	check_quotes2(char head, t_brack *br)
{
	if (head == '\'' && !br->twice)
	{
		if (br->single)
			br->single = 0;
		else
			br->single = 1;
	}
	if (head == '\"' && !br->single)
	{
		if (br->twice)
			br->twice = 0;
		else
			br->twice = 1;
	}
}

static int	checker(int ret, t_brack *brack, t_all *all)
{
	if (ret)
	{
		all->vlast = ret;
		write(1,
			  "bash: syntax error near unexpected token `newline'\n", 51);
	}
	if (brack->single || brack->twice)
	{
		all->vlast = ft_error("Unclosed quotes are detected", 2);
		return (2);
	}
	return (ret);
}

int	check_valid(char *line, t_all *all)
{
	int		i;
	int		ret;
	t_brack	brack;

	brack.single = 0;
	brack.twice = 0;
	ret = EXIT_SUCCESS;
	while (*line != '\0')
	{
		check_quotes2(*line, &brack);
		i = check_symb(&line);
		if (i == 1 || (i == 2 && *line++ != '\0'))
		{
			ret = 2;
			line++;
			while (*line == ' ')
				line++;
			if (*line != '\0' && !check_symb(&line))
				ret = 0;
		}
		line++;
	}
	ret = checker(ret, &brack, all);
	return (ret);
}
