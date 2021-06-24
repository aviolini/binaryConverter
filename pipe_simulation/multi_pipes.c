#include "tools.h"

char ***find_commands(int num_pipes, char **av);

int	main(int ac, char **av)
{
	// int pid;
	(void)ac;
	int num_pipes;
	char ***commands;

	num_pipes = num_of_pipes(av);
	commands = find_commands(num_pipes, av);
	print_commands(commands);
	free_commands(&commands);
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
