#include "../includes/minishell.h"

/**
**
** @return NEED to FREE
*/

char	*get_pwd(void)
{
	char	*buf;

	buf = (char *) malloc(1000);
	if (!buf)
		return (NULL);
	return (getcwd(buf, 1000));
}

int	ft_pwd(void)
{
	char	*buf;

	buf = get_pwd();
	if (!buf)
		return (1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
