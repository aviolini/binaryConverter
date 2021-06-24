#include "tools.h"

int main(int ac, char **av)		//	a.out	ls		grep 	o 		grep 	a 		wc		-l
{
	int pid;
	int num_pipes;
	int fd[2];
	int i;
	int x;
	int **fd_pipe;

	(void)ac;
	num_pipes = 3;
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd_pipe = (int **)malloc(sizeof(int *) * (num_pipes));
	i = -1;
	while (++i < num_pipes)
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < num_pipes)
		pipe(fd_pipe[i]);
	i = -1;
	while (++i <= num_pipes)
	{
		pid = fork();
		printf("i:%d\n", i);
		if (pid == 0)
		{
			if (i != 0)
				if (dup2(fd_pipe[i-1][0], 0) < 0)
					write(fd[1], "Error_1\n", 8);
			if (i != num_pipes)
			{
				if (dup2(fd_pipe[i][1],1) < 0)
					write(fd[1], "Error_2\n", 8);
			}
			// else
			// 	if (dup2(fd[1], 1) < 0)
			// 		write(fd[1], "Error_3\n", 8);
			close_all_fd_pipe(&fd_pipe, num_pipes);
			// close_all_fd_pipe_2(fd_pipe);
			if (i == 0)
			{
				execlp(av[1], av[1], NULL);
				write(fd[1], "Failed\n", 7);
			}
			if (i == 1)
			{
				execlp(av[2],av[2],  av[3], NULL);
				write(fd[1], "Failed\n", 7);
			}
			if (i == 2)
			{
				execlp(av[4], av[4], av[5], NULL);
				write(fd[1], "Failed\n", 7);
			}
			if (i == 3)
			{
				execlp(av[6], av[6], av[7], NULL);
				write(fd[1], "Failed\n", 7);
			}
		}
	}
	// close_all_fd_pipe_2(fd_pipe);
	close_all_fd_pipe(&fd_pipe, num_pipes);
	x = -1;
	while (++x < num_pipes)
			wait(NULL);
	// printf("z:%d\n", z);
	// write(fd[1], "Exit parent\n", 12);
	return (0);
}
