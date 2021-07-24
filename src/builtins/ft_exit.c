#include "../includes/minishell.h"

int	is_number(char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **command, int *res)
{
	int			len;

	len = get_arr_2x_len(command);
	if (len == 1)
	{
		*res = 0;
		exit(EXIT_SUCCESS);
	}
	else if (len > 2)
	{
		*res = 1;
		printf("exit: too many arguments\n");
		return ;
	}
	if (is_number(command[1]))
	{
		*res = ft_atoi(command[1]);
		*res = (unsigned char)(*res);
		exit(*res);
	}
	else
		print_and_exit("numeric argument required\n", 2);
}
