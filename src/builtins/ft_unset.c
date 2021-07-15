#include "../includes/minishell.h"

int			ft_unset(char **command, char ***env)
{
	char	**tmp;

	tmp = command + 1;
	while (*tmp)
	{
		del_line_arr_2x(*tmp, env);
		tmp++;
	}
	return 0;
}