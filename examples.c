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
//	int 	p[2];
//
//	fd_f = open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	dup2(fd_f, 1);
//	printf("ddddd %d\n", fd_f);
//	close(fd_f);
//
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

#include <signal.h>
#include <stdio.h>

//обработчик
void listener(int sig) {
	printf("listener: %d\n", sig);
	exit(EXIT_SUCCESS);
}

//int main() {
//	pid_t child_pid;
//
//	signal(SIGINT, SIG_IGN);
//	child_pid = fork();
//	if (child_pid < 0)
//	{
//		exit(EXIT_FAILURE);
//	}
//	else if (child_pid > 0) {
//		printf("I'm Mother\n");
////		signal(SIGINT, SIG_IGN);
//		sleep(6);
//		printf("M: I'm after SIGINT\n");
//
//	} else {
//		signal(SIGINT, SIG_DFL);
//		printf("I'm daughter\n");
//		sleep(5);
////		raise(SIGINT);
//		printf("D: I'm after SIGINT\n");
//		exit (0);
//	}
//	return 0;
//}
//int main() {
//	pid_t child_pid;
//
//	signal(SIGINT, SIG_IGN);
//	sleep(4);
//	printf("start\n");
//	int i = 0;
//	while(1)
//	{
//		if (i > 3)
//			signal(SIGINT, SIG_DFL);
//		printf("tick %d\n", i);
//		sleep(1);
//		i++;
//	}
//	printf("end\n");
//	return 0;
//}
//int main() {
//	//устанавливаем обработчик для сигнлана SIGINT
//	signal(SIGINT, SIG_DFL);
//	fprintf(stdout, "begin\n");
//	//посылаем сигнал программно
////	raise(SIGINT);
//
//
//	//посылаем сигнал вручную
//	for (int i = 0; i < 100000; ++i) {
//		printf(".\n");
//	}
//	fprintf(stdout, "end\n");
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