#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * Подмена fd с помощью команды dup2
 * @return
 */
//int		main()
//{
//	int		fd_f;
//
//	fd_f = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	dup2(fd_f, 1);
//	close(fd_f);
//	write(1, "hi", 2);
//	printf("%s\n", "hello");
//}


//int		main(int argc, char **argv, char *envp[])
//{
//	int		fd_f;
//	char	*arr[2];
//
//	arr[0] = "/goinfre/main.c";
//	arr[1] = NULL;
//	fd_f = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
////	fd_f = open("/goinfre/main.c", O_WRONLY | O_CREAT | O_TRUNC, 0644);
////	dup2(fd_f, 1);
//	int res = execve("/bin/echo", arr, envp);
//	printf("%d\n", res);
//	close(fd_f);
////	write(1, "hi", 2);
//	printf("%s\n", "hello");
//}


/**
 * execve examle
 * @param argc
 * @param argv
 * @param envp
 * @return
 */
//int		main(int argc, char **argv, char *envp[]) {
//	char* argv_my[] = {"my_program_name", "foo.txt", NULL };
//	if (execve("/bin/cat", argv_my, envp) == -1)
//		perror("Could not execve");
//	return 1;
//}

//int main() {
//	pid_t child_pid;
//
//	child_pid = fork();
//	if (child_pid > 0) {
//		sleep(6);
//	} else {
//		exit (0);
//	}
//	return 0;
//}


//
///**
//**
//** @return
//*/
//int		main()
//{
//	int		pipe_fd[2];
//	int		cpid;
//	char	buf;
//	int		res;
//
//	// create a pipe
//	if (pipe(pipe_fd) == -1)
//		exit(EXIT_FAILURE);
//	if ((cpid = fork()) == -1)
//		exit(EXIT_FAILURE);
//	if (cpid == 0)
//	{
//		// we don't use output fd. So, close it
//		close(pipe_fd[1]);
//		while(1)
//		{
//			printf("daughter\n");
//			// reading from pipe
//			res = read(pipe_fd[0], &buf, 1);
//			// print to terminal
//			printf("read: %d [%c]\n", res, buf);
//			if (res <= 0)
//				break;
//		}
//		// reading is complete. Close pipe
//		close(pipe_fd[0]);
//		exit(EXIT_SUCCESS);
//	}
//	else
//	{
//		// we don't use input fd. So, close it
//		close(pipe_fd[0]);
//		write(pipe_fd[1], "hello to my daughter", 20);
//		close(pipe_fd[1]);
//		int status;
//		for (int i = 0; i < 30; ++i) {
//			printf("parent\n");
//		}
//		res = waitpid(cpid, &status, 0);
//		printf("%d\n", res);
//	}
//
//
//}