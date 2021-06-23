# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
// # include <dirent.h>
// # include <errno.h>
// # include <string.h>
// # include <curses.h>
// # include <term.h>
// # include <termios.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <signal.h>
// #include <sys/ioctl.h>

int close_all_fd_pipe(int ***fd_pipe, int num)
{
	int i;
	int x;

	i = -1;
	while (++i < num)
	{
		x = -1;
		while (++x < 2)
			close((*fd_pipe)[i][x]);
	}	
	return (0);
}

int close_all_fd_pipe_2(int **fd_pipe)
{
	close(fd_pipe[0][0]);
	close(fd_pipe[0][1]);
	close(fd_pipe[1][0]);
	close(fd_pipe[1][1]);
	close(fd_pipe[2][0]);
	close(fd_pipe[2][1]);
}


int two_pipes(int ac, char **av)
{
	int pid;
	int num_pipes;
	int fd[2];
	int i;
	int **fd_pipe;

	num_pipes = 3;
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd_pipe = (int **)malloc(sizeof(int *) * (num_pipes-1));
	i = -1;
	while (++i < num_pipes)
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < num_pipes)
		pipe(fd_pipe[i]);
	pid  = fork();
	if (pid == 0)
	{
		write(fd[1], "Child_1\n", 8);
		dup2(fd_pipe[0][1], 1);
		close_all_fd_pipe(&fd_pipe, num_pipes);
		execlp(av[1], av[1], NULL);
		write(fd[1], "Failed_1\n", 9);
	}
	else
	{
		//	a.out	ls		grep 	o 		grep 	a 		wc 		-l
		// av[0]	av[1]	av[2]	av[3]	av[4]	av[5]	av[6]	av[7]

		// close_all_fd_pipe(&fd_pipe, num_args);
		write(fd[1], "Wait_1\n", 7);	
		waitpid(pid, NULL, 0);
		write(fd[1], "Start_1\n", 8);	
		i = -1;
		while (++i < num_pipes )
		{
			write(fd[1], "prefork\n", 8);
			printf("i:%d\n", i);
			pid = fork();
			if (pid == 0)
			{
				write(fd[1], "Child_2\n", 8);		
				if (i == 0)
				{	
					dup2(fd_pipe[i][0], 0);	
					dup2(fd_pipe[i+1][1], 1);
					printf(" ciao1\n");
					close_all_fd_pipe(&fd_pipe, num_pipes);	
					write(fd[1], "Execlp_1\n", 9);
					execlp(av[2], av[2], av[3], NULL);
					write(fd[1], "Failed_2\n", 9);		
				}
				if (i == 1)
				{
					dup2(fd_pipe[i][0], 0);	
					dup2(fd_pipe[i+1][1], 1);
					close_all_fd_pipe(&fd_pipe, num_pipes);
					printf(" ciao2\n");
					write(fd[1], "Execlp_2\n", 9);
					execlp(av[4], av[4], av[5], NULL);
					write(fd[1], "Failed_3\n", 9);			
				}
				if (i == 2)
				{
					write(fd[1], "Last_Child\n", 11);
					dup2(fd_pipe[i][0], 0);	
					close_all_fd_pipe(&fd_pipe, num_pipes);
					execlp(av[6], av[6], av[7], NULL);
					write(fd[1], "Failed_3\n", 9);		
				}
			}
			else 
			{
				close_all_fd_pipe(&fd_pipe, num_pipes);
				write(fd[1], "Wait_2\n", 7);
				wait(NULL);
				write(fd[1], "Exit_parent\n", 12);
				if (i == 1)
					return(0);
			}
		}
	}
	return (0);
}

int one_pipe_one_fork(int ac, char **av)
{	
	int pid;
	int fd_pipe[2];
	int fd[2];

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
	}
	else
	{
		// printf("pid_P:%d\n", pid);
		// write(fd, "Waiting\n", 8);
		int w = wait(NULL);
		// printf("wait:%d\n", w);
		// write(fd, "Parent\n", 7);
		close(fd_pipe[1]);                  //SE COMMENTATO NON CHIUDE IL PROGRAMMA
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		execlp(av[2], av[2],av[3], NULL);
		write(fd[1], "Failed\n", 7);

	}
	return 0;
}

int one_pipe_two_forks(int ac, char **av)
{	
	int pid;
	int fd_pipe[2];
	int fd0= dup(0);
	int fd1= dup(1);
	int w;

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		// printf("pid_C:%d\n", pid);
		// write(fd1, "Child\n", 6);
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		execlp(av[1], av[1], NULL);
		write(fd1, "Failed\n", 7);	
	}
	else
	{
		// printf("pid_P:%d\n", pid);
		// write(fd1, "Waiting\n", 8);
		// w = wait(NULL);
		w = waitpid(pid, NULL, 0);		
		// printf("wait:%d\n", w);
		// write(fd1, "Parent\n", 7);
		pid = fork();
		if (pid == 0)
		{
			// printf("pid_C2:%d\n", pid);
			// write(fd1, "Child2\n", 7);
			close(fd_pipe[1]);
			dup2(fd_pipe[0], 0);
			close(fd_pipe[0]);
			execlp(av[2], av[2],av[3], NULL);
			write(fd1, "Failed\n", 7);	
		}
		else
		{
			// write(fd1, "Waiting\n", 8);
			// printf("pid_Last:%d\n", pid);
			close(fd_pipe[1]);					//SE COMMENTATO NON CHIUDE
			close(fd_pipe[0]);
			w = waitpid(pid, NULL, 0);
			// printf("wait:%d\n", w);
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

int main(int ac, char **av)
{
	//one_pipe_one_fork(ac,av);				//	a.out ls grep a
	// one_pipe_two_forks(ac,av);			//	a.out ls grep a
	two_pipes(ac,av);						//	a.out	ls		grep 	o 		grep 	a 		wc		-l
											// av[0]	av[1]	av[2]	av[3]	av[4]	av[5]	av[6]	av[7]
	return (0);
}