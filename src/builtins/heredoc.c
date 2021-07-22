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

void handler_sigint2(int sign)
{
	if (sign == SIGINT)
	{
		printf("hel: %d", flag);
//		raise(SIG);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		flag = 1;
	}
}


int	exec_heredoc(char *breaker, t_all *all, int *pipe_fd)
{
	char	*line;
	int		fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);

//	if (init_heredoc(fd) != 0)
//		return (-1);
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, breaker, ft_strlen(line) + 1) == 0 || flag)
		{
			break ;
		}
		if (line)
			unc_envs(&line, all);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line == NULL && !flag)
		printf("minishell: here-doc delimited by EOF\n");
	free(line);
	close(fd);
	exit(0);
}