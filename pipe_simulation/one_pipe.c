#include "tools.h"

int one_pipe_one_fork(int ac, char **av);
int one_pipe_two_forks(int ac, char **av);

int main(int ac, char **av)
{
	one_pipe_one_fork(ac,av);				//	a.out ls grep a
	// one_pipe_two_forks(ac,av);			//	a.out ls grep a

	return (0);
}

int one_pipe_one_fork(int ac, char **av)
{	
	int pid;
	int fd_pipe[2];
	int fd[2];

	(void)ac;
	fd[0] = dup(0);
	fd[1] = dup(1);
	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		// printf("pid_C:%d\n", pid);
		// write(fd, "Child\n", 6);
		close(fd_pipe[0]);  
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		execlp(av[1], av[1], NULL);
		write(fd[1], "Failed\n", 7);
		exit(1);	
	}
	else
	{
		// printf("pid_P:%d\n", pid);
		// write(fd, "Waiting\n", 8);
		wait(NULL);
		// write(fd, "Parent\n", 7);
		close(fd_pipe[1]);                  //SE COMMENTATO NON CHIUDE IL PROGRAMMA
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		execlp(av[2], av[2],av[3], NULL);
		write(fd[1], "Failed\n", 7);
		exit(1);

	}
	return 0;
}

int one_pipe_two_forks(int ac, char **av)
{	
	int pid;
	int fd_pipe[2];
	// int fd0= dup(0);
	int fd1= dup(1);

	(void)ac;
	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		// printf("pid_C:%d\n", pid);
		// write(fd1, "Child\n", 6);
		close(fd_pipe[0]);
		if (dup2(fd_pipe[1], 1) < 0)
			write(fd1, "Error\n", 6);
		close(fd_pipe[1]);
		execlp(av[1], av[1], NULL);
		write(fd1, "Failed\n", 7);
		exit(1);	
	}
	else
	{
		// printf("pid_P:%d\n", pid);
		// write(fd1, "Waiting\n", 8);
		// w = wait(NULL);
		waitpid(pid, NULL, 0);		
		// write(fd1, "Parent\n", 7);
		pid = fork();
		if (pid == 0)
		{
			// printf("pid_C2:%d\n", pid);
			// write(fd1, "Child2\n", 7);
			close(fd_pipe[1]);
			if (dup2(fd_pipe[0], 0) < 0)
				write(fd1, "Error\n", 6);
			close(fd_pipe[0]);
			execlp(av[2], av[2],av[3], NULL);
			write(fd1, "Failed\n", 7);
			exit(1);
		}
		else
		{
			// write(fd1, "Waiting\n", 8);
			// printf("pid_Last:%d\n", pid);
			close(fd_pipe[1]);					//SE COMMENTATO NON CHIUDE
			close(fd_pipe[0]);
			waitpid(pid, NULL, 0);
			// exit(1);
			// dup2(fd0, 0);
			// close(fd0);
			// dup2(fd1, 1);
			// close(fd1);
			write(fd1, "Ok\n", 3);
		}
	}
	return 0;
}
