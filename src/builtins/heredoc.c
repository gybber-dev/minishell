#include "../includes/minishell.h"

static int	init_heredoc(int fd[2])
{
	char	buf[1000];

	fd[1] = open(HERE_DOC_FILE, O_WRONLY | O_APPEND | O_CREAT, 0664);
	fd[0] = open(HERE_DOC_FILE, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1)
		return (ft_perror("here_doc", 1));
	write(fd[1], "\n", 1);
	while (read(fd[0], buf, 1000) > 0)
		;
	return (0);
}

int	exec_heredoc(char *breaker, t_all *all)
{
	int		disable_expansion;
	char	*line;
	int		fd[2];

	if (init_heredoc(fd) != 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, breaker, ft_strlen(line) + 1) == 0)
			break ;
		if (line)
			unc_envs(&line, all);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	if (line == NULL)
		printf("minishell: here-doc error\n");
	free(line);
	close(fd[1]);
	return (fd[0]);
}