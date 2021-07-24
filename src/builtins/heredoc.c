#include "../includes/minishell.h"

int	exec_heredoc(char *breaker, t_all *all)
{
	char	*line;
	int		fd = open(HERE_DOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0666);

	while (1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, breaker, ft_strlen(line) + 1) == 0)
		{
			break ;
		}
		if (line)
			unc_envs(&line, all);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line == NULL)
		printf("minishell: here-doc delimited by EOF\n");
	free(line);
	close(fd);
	exit(0);
}