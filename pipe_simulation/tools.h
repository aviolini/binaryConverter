#ifndef TOOLS_H
# define TOOLS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_com
{
	char **command;
	struct s_com *next;
}	t_com;


int		ft_strlen(char *line);
char	*ft_strdup(char *line);
int		ft_strcmp(char *line, char c);
int		close_all_fd_pipe(int **fd_pipe, int num);
int		free_commands(char ****commands);
void	free_pipes(int **pipe_fd, int num_pipes);
int		num_of_pipes(char **av);
int		print_commands(char ***commands);
void	print_list(t_com **list);
void	free_list(t_com ***list);

#endif