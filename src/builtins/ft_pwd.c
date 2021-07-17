#include "../includes/minishell.h"

/**
**
** @return NEED to FREE
*/
char		*get_pwd(void)
{
	char	*buf;

	if (!(buf = (char *) malloc(1000)))
		return (NULL);
	return (getcwd(buf, 1000));
}

int			ft_pwd(void)
{
	char	*buf;

	if (!(buf = get_pwd()))
		return (1);
	printf("%s\n", buf);
	free(buf);
	return 0;
}