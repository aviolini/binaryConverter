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

int ft_strlen(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		i++;
	return (i);
}

char *ft_strdup(char *line)
{
	int i;
	char *new;
	int len;
	
	len = ft_strlen(line);
	i = -1;
	new = (char *)malloc(sizeof(char) *(len + 1));
	new[len] = '\0';
	while (line[++i])
		new[i] = line[i];
	return (new);
}

int ft_strcmp(char *line, char c)
{
	int i;

	i = -1;
	if (!line)
		return(-1);
	while (line[++i])
	{
		if (line[i] == c)
			return (i);
	}
	return (-1);
}

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

int free_commands(char ****commands)
{
	int i;
	int x;

	i = -1;
	while ((*commands)[++i])
	{
		x = -1;
		while((*commands)[i][++x])
			free((*commands)[i][x]);
		free((*commands)[i]);
	}
	free((*commands));
	*commands = NULL;
	return (1);
}

int	num_of_pipes(char **av)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while(av[++i])
		if (av[i][0] == '|' && av[i][1] == '\0')
			c++;
	printf("num_pipes:%d\n",c);
	return(c);
}

char ***find_commands(int num_pipes, char **av)
{
	int i;
	int x;
	int y;
	int z;
	char ***commands;
	commands = (char ***)malloc(sizeof(char **) * (num_pipes + 2));
	x = 0;
	z = 0;
	i = 0;
	while (av[i] && av[++i])
	{
		if ((av[i][0] == '|' && !(av[i][1])) || (!av[i + 1]))
		{
			// printf("av:%s\n",av[i]);
			// printf("i:%d\tz:%d\n",i,z);
			if ((!av[i + 1]))
				i++;
			commands[x] =(char **)malloc(sizeof(char *) * (i - z + 1));
			y = 0;
			z++;
			while (z < i)
			{
				commands[x][y] = ft_strdup(av[z]);
				// printf("av_strdup:%s\n",av[z]);			
				y++;
				z++;
			}
			commands[x][y] = NULL;
			z = i;
			x++;
		}
	}
	commands[x] = NULL;
	return (commands);
}

int print_commands(char ***commands)
{
	int x;
	int i;

	x = -1;
	while (commands[++x])
	{
		i = -1;
		printf("----\n");
		while (commands[x][++i])
			printf("commands:%s\t %p\n", commands[x][i], commands[x][i]);
	}
	return(0);
}

int	multi_pipes(int ac, char **av)
{
	// int pid;
	(void)ac;
	int num_pipes;
	char ***commands;

	(void)commands;
	num_pipes = num_of_pipes(av);
	commands = find_commands(num_pipes, av);
	print_commands(commands);
	free_commands(&commands);
	return (0);
}


int three_pipes(int ac, char **av)
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
	}
	else
	{
		// printf("pid_P:%d\n", pid);
		// write(fd, "Waiting\n", 8);
		int w = wait(NULL);
		printf("wait:%d\n", w);
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
	// int fd0= dup(0);
	int fd1= dup(1);
	int w;

	(void)ac;
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
		printf("wait:%d\n", w);
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
			printf("wait:%d\n", w);
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
	// three_pipes(ac,av);						//	a.out	ls		grep 	o 		grep 	a 		wc		-l
												// av[0]	av[1]	av[2]	av[3]	av[4]	av[5]	av[6]	av[7]
	multi_pipes(ac, av);					//	a.out ls "|" grep o "|"	grep a "|" grep	t "|" wc -l
	return (0);
}