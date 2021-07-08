#include "tools.h"

int find_commands(t_com **list, char **av, int num);
t_com *set_temp(t_com **list);

int main(int ac, char **av)
{
	int num_pipes;
	int i;
	int pid;
	int **fd_pipe;
	t_com **list;
	t_com *temp;

	(void)ac;
	i = -1;
	num_pipes = 0;
	while (av[++i])
		if (av[i][0] == '|' && !(av[i][1]))
			num_pipes++;
	fd_pipe = (int **)malloc(sizeof(int *) * num_pipes);
	i = -1;
	while (++i < num_pipes)
		fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < num_pipes)
		pipe(fd_pipe[i]);

	list = (t_com **)malloc(sizeof(t_com *));
	*list = NULL;
	find_commands(list, av, num_pipes);
	print_list(list);
	temp = *list;
	i = -1;
	// while (++i <= num_pipes)
	while (temp)
	{
		i++;
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				if (dup2(fd_pipe[i -1][0] , 0) < 0)
					perror("Error_fd:");
			if (i != num_pipes)
				if (dup2(fd_pipe[i][1], 1) < 0)
					perror("Error_fd:");
			close_all_fd_pipe(fd_pipe, num_pipes);
			execvp(temp->command[0], temp->command);
			perror("Exec failed:");
			free_pipes(fd_pipe,num_pipes);
			free_list(&list);
			exit(1);
		}
		temp = temp->next;
		/*	NEW HANDLING	*/
		if (i != 0)
			if (close(fd_pipe[i -1][0]) < 0)
				perror("Error_close:");
		if (i != num_pipes)
			if (close(fd_pipe[i][1]) < 0)
				perror("Error_close:");
		wait(NULL);
		/*					*/
	}
	/*	OLD HANDLING	*/
	// int x;
	// close_all_fd_pipe(fd_pipe, num_pipes);
	// x = -1;
	// while (++x < num_pipes)
	// 	wait(NULL);
	/*					*/
	write(1, "Finish\n", 7);
	free_pipes(fd_pipe,num_pipes);
	free_list(&list);
	close(1);
	close(2);
	close(0);
	return (0);
}

t_com *set_temp(t_com **list)
{
	t_com *temp;
	t_com *new;

	new = (t_com *)malloc(sizeof(t_com));
	// printf("*list_in:%p\n",*list);
	if (!list)
		return(NULL);
	if (!(*list))
	{
		*list = new;
		(*list)->next = NULL;
		return (*list);
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	// print_list(&temp);
	return(new);
}

int find_commands(t_com **list, char **av, int num)
{
	int i;
	int x;
	int z;
	t_com *temp;
	(void)num;

	i = 0;
	x = 1;
	
	while (av[i] && av[++i])
	{
		if ((av[i][0] == '|' && av[i][1] == '\0') || !(av[i + 1]))
		{
			if (!(av[i +1]))
				i++;
			// printf("i:%d\tx:%d\n",i,x);
			temp = set_temp(list);
			temp->command = (char **)malloc(sizeof(char *) * (i - x + 1));
			// temp->next = NULL;
			z = -1;
			while (x < i)
			{
				temp->command[++z] = ft_strdup(av[x]);
				// printf("temp->command: %s\n", temp->command[z]);
				x++;
			}
			x = i + 1;
			temp->command[++z] = NULL;
		}
	}
	return(0);
}

