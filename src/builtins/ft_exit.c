#include "../includes/minishell.h"

int 			ft_exit(char **command)
{
	int			status;
	int			len;

	len = get_arr_2x_len(command);

	if (len == 1)
		exit(EXIT_SUCCESS);
	if (len > 2)
		return (EXIT_FAILURE);
	status = ft_atoi(command[1]);
	exit(status);
}
