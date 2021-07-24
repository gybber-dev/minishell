#include "../includes/minishell.h"

void	print_and_exit(char *msg, int res)
{
	ft_putstr_fd(msg, 1);
	exit(res);
}

int	free_and_return(char **mem, int res)
{
	if (*mem)
		free(*mem);
	*mem = NULL;
	return (res);
}

int	ft_error(char *err_msg, int res)
{
	printf("%s\n", err_msg);
	return (res);
}

int	ft_perror(char *msg, int res)
{
	perror(msg);
	return (res);
}
