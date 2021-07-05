/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 * loop over commands by sharing
 * pipes.
 */
static void
pipeline(char ***cmd)
{
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL) {
		pipe(fd);
		printf("p[%d, %d]\n", fd[0], fd[1]);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL) {
				dup2(fd[1], 1);
				close(fd[1]);
			}
			close(fd[1]);
			close(fd[0]);
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}

}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int
main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-al", NULL};
	char *grep[] = {"grep", "o", NULL};
	char *wc[] = {"wc", "-l", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {ls, grep, wc, NULL};

	pipeline(cmd);
	int fd[2];
	pipe(fd);
	printf("pipe[%d, %d]\n", fd[0], fd[1]);
	return (0);
}
