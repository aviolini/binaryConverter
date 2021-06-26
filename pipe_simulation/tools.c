#include "tools.h"

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
	if (!new)
		return (NULL);
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

int close_all_fd_pipe(int **fd_pipe, int num)
{
	int i;

	i = -1;
	while (++i < num)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
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
		{
			free((*commands)[i][x]);
			(*commands)[i][x] = NULL;
		}
		free((*commands)[i]);
		(*commands)[i] = NULL;
	}
	free((*commands));
	*commands = NULL;
	return (1);
}

void free_pipes(int **pipes, int num)
{
	int i;

	i = -1;
	while (++i < num)
		free(pipes[i]);
	free(pipes);
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
			printf("commands:%s\n", commands[x][i]);
	}
	return(0);
}

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
