#include "../includes/minishell.h"

int	ft_unset(char **command, char ***env)
{
	char	**tmp;
	int		err_status;

	err_status = 0;
	tmp = command + 1;
	while (*tmp)
	{
		err_status = del_line_arr_2x(*tmp, env);
		if (err_status)
			return (err_status);
		tmp++;
	}
	return (EXIT_SUCCESS);
}
