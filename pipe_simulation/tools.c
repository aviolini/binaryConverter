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