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
