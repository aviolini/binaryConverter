
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_com
{
	char **command;
	struct s_com *next;
}	t_com;

void print_list(t_com **list)
{
	t_com *temp;
	int i;

	printf("-----\n");
	if (!list || !(*list))
		printf("Empty list\n");
	temp = *list;
	while (temp)
	{
		i = -1;
		while (temp->command[++i])
			printf("%s\n", temp->command[i]);
		temp = temp->next;
		printf("-----\n");
	}
}

char *ft_strdup(char *line)
{
	int i;
	int len;
	char *new;

	len = 0;
	i = -1;
	while (line[len])
		len++;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (line[++i])
		new[i] = line[i];
	new[len] = '\0';
	return(new);
}

void free_list(t_com ***list)
{
	t_com *temp;
	t_com *temp2;
	int i;

	temp = **list;
	while(temp)
	{
		temp2 = temp;
		temp = temp->next;
		i = -1;
		while(temp2->command[++i])
			free(temp2->command[i]);
		free(temp2->command);
		free(temp2);
	}
	free(*list);
	*list = NULL;
}

void free_pipes(int **pipes, int num)
{
	int i;

	i = -1;
	while (++i < num)
		free(pipes[i]);
	free(pipes);
}

void close_fd(int **fd, int num)
{
	int i;

	i = -1;
	while (++i < num)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
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

int main(int ac, char **av)
{
	int num_pipes;
	int i;
	int x;
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
			close_fd(fd_pipe, num_pipes);
			execvp(temp->command[0], temp->command);
			perror("Exec failed:");
		}
		temp = temp->next;
	}
	close_fd(fd_pipe, num_pipes);
	x = -1;
	while (++x < num_pipes)
		wait(NULL);
	free_pipes(fd_pipe,num_pipes);
	free_list(&list);
	close(0);
	close(1);
	close(2);
	return (0);
}