#include "../includes/minishell.h"
#include <fcntl.h>

/**
 *
 * @param messages
 */
void		ft_echo(char *messages)
{
	int		fd[2];
	int		fd_f;

//	fd[0] = -1;
//	fd[2] = -2;
//	pipe(fd);
//	printf("[%d, %d]\n", fd[0], fd[1]);
	fd_f = open("buf", O_RDWR);
	dup2(fd_f, 1);
	write(1, "hi", 2);
	close(fd_f);
	printf("%s\n", "hello");
}