/**
** Reads data from "from" and writes to "to".
** How to usage?
**	int fd_write = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
**	int fd_read = open("foo.txt", O_RDONLY);
**	read_from_write_to(fd_read, fd_write);
** @param from	input fd
** @param to	output fd
*/

void	read_from_write_to(int from, int to)
{
	char	*buf;
	int		res;

	buf = (char *)malloc(2);
	buf[1] = 0;
	buf[0] = 'e';
	printf("%s\n", buf);
	while(1)
	{
		res = read(from, buf, 1);
		if (res == 0)
			break;
		write(to, buf, 1);
	}
	free(buf);
}
/**
** Redirects stdout of command to buffer variable. Needs to free buffer
** Buffer size is 1000
** @param cmd list of commands
** @return malloced pointer to result of command
*/

char 	*get_command_result(char **cmd, char **env)
{
	int fd[2];
	char *buffer;
	char *path;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (env){
			path = find_binary(cmd[0], get_value(env, "PATH"));
			execve(path, cmd, env);
		}else{
			execvp(cmd[0], cmd);
		}
	}
	else
	{
		int size = (int)read(fd[0], buffer, 1000);
		if ( (size>0) && (size < (int)sizeof(buffer)) )
		{
			buffer[size]='\0';
		}
		close(fd[0]);
		close(fd[1]);
	}
	return buffer;
}

char 	*get_stdout_fun_result(char **cmd, int (*fun)(char **, char **), char
**env)
{
	int fd[2];
	char *buffer;

	buffer = malloc(1000);
	pipe(fd);
	if (fork() == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (env)
			fun(cmd, env);
		else
			fun(cmd, NULL);
	}
	else
	{
		int size = read(fd[0], buffer, 1000);
		if ( (size>0) && (size < (int)sizeof(buffer)) )
		{
			buffer[size]='\0';
		}
		close(fd[0]);
		close(fd[1]);
	}
	return buffer;
}