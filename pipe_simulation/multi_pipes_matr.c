#include "tools.h"

char ***find_commands(int num_pipes, char **av);

int	main(int ac, char **av)
{
	(void)ac;
	int num_pipes;
	char ***commands;
	int i;
	int fd[2];
	int **pipe_fd;
	int pid;

	fd[0] = dup(0);
	(void)fd[0];
	fd[1] = dup(1);
	num_pipes = num_of_pipes(av);
	commands = find_commands(num_pipes, av);
	print_commands(commands);
	pipe_fd = (int **)malloc(sizeof(int *) * num_pipes);
	i = -1;
	while(++i < num_pipes)
		pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < num_pipes)
		pipe(pipe_fd[i]);
	i = -1;
	while(++i <= num_pipes)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				if (dup2(pipe_fd[i - 1][0], 0) < 0)
					write(fd[1], "Error_fd1\n", 11);
			}
			if (i != num_pipes)
			{
				if (dup2(pipe_fd[i][1], 1) < 0)
					write(fd[1], "Error_fd2\n", 11);
			}
			close_all_fd_pipe(pipe_fd, num_pipes);
			close(fd[0]);
			close(fd[1]);
			execvp(commands[i][0], commands[i]);
			write(fd[1], "Error_exec\n", 11);
			free_commands(&commands);
			free_pipes(pipe_fd, num_pipes);
			return(1);
		}
		/*	NEW HANDLING	*/
		if (i != 0)
			if (close(pipe_fd[i -1][0]) < 0)
				perror("Error_close:");
		if (i != num_pipes)
			if (close(pipe_fd[i][1]) < 0)
				perror("Error_close:");
		wait(NULL);
		/*					*/
	}
	/*	OLD HANDLING	*/
	// int x;
	// close_all_fd_pipe(pipe_fd, num_pipes);
	// x = -1;
	// while (++x < num_pipes)
	// 	wait(NULL);
	/*					*/
	free_commands(&commands);
	free_pipes(pipe_fd, num_pipes);
	write(fd[1], "Finish\n", 7);
	close(fd[0]);
	close(fd[1]);
	close(1);
	close(2);
	close(0);
	return (0);
}

char ***find_commands(int num_pipes, char **av)
{
	int i = 0;
	int x = 0;
	int z = 0;
	int y;
	char ***commands;

	if (!(commands = (char ***)malloc(sizeof(char **) * (num_pipes + 2))))
		return (NULL);
	while (av[i] && av[++i])
		if ((av[i][0] == '|' && !(av[i][1])) || (!av[i + 1]))
		{
			if ((!av[i + 1]))
				i++;
			if (!(commands[x] =(char **)malloc(sizeof(char *) * (i - z + 1))))
				return (NULL);
			y = 0;
			z++;
			while (z < i)
				if (!(commands[x][y++] = ft_strdup(av[z++])))
					return(NULL);
			commands[x][y] = NULL;
			z = i;
			x++;
		}
	commands[x] = NULL;
	return (commands);
}
