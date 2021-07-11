#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int i = 0;
typedef struct s_fix_fd
{
	int			in;
	int			out;
}				t_fix_fd;

/**
		ls -l | grep re | wc -l > 1
**/

void 		read_from_write_to(int from, int to);

void		do_parent_pipe(char *oper, char ***cmd, int (*fd)[2],
						   int *backup_stdin, int pid)
{
	int status;

	printf("parent: %d\n", i);
	close((*fd)[1]);
//			writes pipe's output to 0
	dup2((*fd)[0], 0);
	waitpid(pid, &status, 0);
	close((*fd)[0]);
	if (*(cmd + 1) == NULL)
	{
		printf("closing all\n");
		dup2(*backup_stdin, 0);
		close(*backup_stdin);
	}
}


void		do_daughter_pipe(char *oper, char ***cmd, int (*fd)[2])
{
	printf("daughter: %d\n", i);
	// if not last command write result to the pipe
	if (*(cmd + 1) != NULL)
		dup2((*fd)[1], 1);
	close((*fd)[1]);
	close((*fd)[0]);
	execvp((*cmd)[0], *cmd);
	fprintf(stderr, "Failed to execute '%s'\n", (*cmd)[0]);
	exit(1);
}

/**
** Reads data from "from" and writes to "to".
** How to usage?
**	int fd_write = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
**	int fd_read = open("foo.txt", O_RDONLY);
**	read_from_write_to(fd_read, fd_write);
** @param from	input fd
** @param to	output fd
*/
void 		read_from_write_to(int from, int to)
{
	char	*buf;
	int 	res;

	buf = (char *)malloc(2);
	buf[1] = 0;
	buf[0] = 0;
	while(1)
	{
		res = read(from, buf, 1);
		if (res == 0)
			break;
		write(to, buf, 1);
	}
	free(buf);
}


void		pipeline(char ***cmd, char *oper, int flag)
{
//	int fd_write = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	int fd_f = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid_t pid;
	char prev;
	int fd[2];
	int backup_stdin = dup(0);
	prev = 0;

	while (*cmd != NULL)
	{
		if ((*oper == '|' || (*oper == 0 && prev == '|')) && prev != '>')
		{
			printf("spec is %c\n", *oper);
			printf("ITER [%d]\t", i);
			pipe(fd);
			printf("%c\tpipe[%d, %d]\n", *oper, fd[0], fd[1]);
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
				do_daughter_pipe(oper, cmd, &fd);
			else
				do_parent_pipe(oper, cmd, &fd, &backup_stdin, pid);
		}
		if (*oper == '>' && prev != '>')
		{
			printf("spec is %c\n", *oper);
			pipe(fd);
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0) {
				do_daughter_pipe(oper, cmd, &fd);
			} else {
				do_parent_pipe(oper, cmd, &fd, &backup_stdin, pid);
			}
		}
		if (prev == '>')
		{
			printf("prev is %c\n", prev);
			pipe(fd);
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
			{
				int		fd_file;

				fd_file = open(**cmd, O_RDWR | O_TRUNC | O_CREAT, 0644);
				printf("check %d %s\n", fd_file, **cmd);
				if (fd_file == -1)
				{
					perror("error >");
					return;
				}
				if (*(cmd + 1) != NULL)
				{
					if (*oper == '>')
						dup2(fd[1], fd_file);
					else
						dup2(fd[1], 1);
				}
				read_from_write_to(0, fd_file);
				close(fd_file);
				close(fd[1]);
				close(fd[0]);
			}
			else
				do_parent_pipe(oper, cmd, &fd, &backup_stdin, pid);
		}

		prev = *oper;
		oper++;
		cmd++;
		i++;
	}
	write(1, "check fd\n", 9);
}

// ls -al | grep o | grep a | wc -l
// ls -al | grep o | grep a | wc -l > 1
// ls > 1 | grep o

int main()
{
	char *empty[] = {"", NULL};
	char *ls[] = {"ls", "-al", NULL};

	char *grep1[] = {"grep", "-a", "o", NULL};
//	char *grep2[] = {"grep", "a", NULL};
//	char *wc[] = {"wc", "-l", NULL};
//	char *file[] = {"1", NULL};
	char *f1[] = {"1", NULL};
	char *f2[] = {"2", NULL};
//	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {empty, f1, f2, NULL}; //  > 1 > 2
//	char **cmd[] = {ls, f1, grep1, NULL}; // ls > 1 | grep o
//	char **cmd[] = {ls, grep1, f1, f2, NULL}; // ls | grep o > 1 > 2
//	char **cmd[] = {ls, grep1, grep2, wc, file, NULL};
	char oper[] = ">>";
	int	flag = 0;
	if (*oper)
		flag = 1;
	pipeline(cmd, oper, flag);
	int fd[2];
	pipe(fd);
	printf("Do you see a pipe leak? pipe[%d, %d]\n", fd[0], fd[1]);
	return (0);
}