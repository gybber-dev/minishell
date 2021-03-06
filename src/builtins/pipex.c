#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/**
		ls -l | grep re | wc -l
**/


void		pipeline(char ***cmd)
{
//	int fd_write = open("here.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	int fd_f = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid_t pid;
	int fd[2];
	int backup_stdin = dup(0);
	int i = 0;

	while (*cmd != NULL)
	{
		printf("ITER [%d]\t", i);
		pipe(fd);
		printf("pipe[%d, %d]\n", fd[0], fd[1]);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			printf("daughter: %d\n", i);
			// if not last command write result to the pipe
			if (*(cmd + 1) != NULL)
				dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			execvp((*cmd)[0], *cmd);
			fprintf(stderr, "Failed to execute '%s'\n", (*cmd)[0]);
			exit(1);
		}
		else
		{
			int status;
			printf("parent: %d\n", i);
			close(fd[1]);
//			writes pipe's output to 0
			dup2(fd[0], 0);
			waitpid(pid, &status, 0);
			if ( WIFEXITED(status) )
			{
				int exit_status = WEXITSTATUS(status);
				printf("Exit status of the child was %d\n",
					   exit_status);
			}
			close(fd[0]);
			if (*(cmd + 1) == NULL)
			{
				printf("closing all\n");
				dup2(backup_stdin, 0);
				close(backup_stdin);
			}

		}
		cmd++;
		i++;
	}
	write(1, "check fd\n", 9);
}

// ls -al | grep o | grep a | wc -l

// int main()
// {
// 	char *ls[] = {"ls", "1231312312", NULL};
// 	char *grep1[] = {"grep", "o", NULL};
// 	char *grep2[] = {"grep", "a", NULL};
//// 	char *wc[] = {"wc", "-l", NULL};
// //	char *cat[] = {"cat", "-e", NULL};
// 	char **cmd[] = {ls, grep1, grep2, NULL};
//
// 	pipeline(cmd);
// 	int fd[2];
// 	pipe(fd);
// 	printf("Do you see a pipe leak? pipe[%d, %d]\n", fd[0], fd[1]);
// 	return (0);
// }