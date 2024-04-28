
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h> 

int main(int argc, char **argv, char **envp) {
	//infile cmd1 cmd2 outfile
	(void)argc;
	(void)argv;
	int pid1;
	int pid2;
	int pipe_fd[2];
	int infile_fd;
	int outfile_fd;
	char *args1[2];
	char *args2[3];

	printf("bonjour parent\n");
	pipe(pipe_fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("bonjour enfant 1\n");
		args1[0] = "cat";
		args1[1] = NULL;
		infile_fd = open("infile", O_RDONLY);
		dup2(infile_fd, STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execve("/usr/bin/cat", args1, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		printf("bonjour enfant 2\n");
		args2[0] = "wc";
		args2[1] = "-l";
		args2[2] = NULL;
		outfile_fd = open("outfile", O_WRONLY| O_CREAT | O_TRUNC, 0644);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(outfile_fd, STDOUT_FILENO);
		execve("/usr/bin/wc", args2, envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while (wait(NULL) > 0)
		;
	printf("au revoir parent\n");
	return (0);
}

// 0    	1		2		3		4
// ls  | wc   |  grep  | echo |    cat

// ls <- entree fichier
// ls -> devant
// wc <- derriere
// wc -> devant
// grep <- derriere
// grep -> devant
// echo <- derriere
// echo -> devant
// cat <- derriere
// cat -> sortie fichier

// if i == 0
// 	lire fichier
// if i == dernier
// 	ecrire fichier
