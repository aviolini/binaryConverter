/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_kill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:14:30 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/04 16:33:09 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

# define STEP 	scanf("%c", &scan);

int ft_exit(int status)
{
	exit(status);
}

int	ft_exit_error(int status, char *s)
{
	if (status == 0)
	{
		
		perror(s);
		return(ft_exit(errno));
	}
	else
	{
		printf("%s\n", s);
		return(ft_exit(status));
	}
}

int main (int ac, char **av)
{
	unsigned int i;
	int temp_pid;
	int pid[5];
	int num_procs;
	char scan;

	i = 0;
	num_procs = 5;
	while (i < num_procs)
	{
		temp_pid = fork();
		if (temp_pid == -1)
			ft_exit_error(0, "Fork");
		if (temp_pid == 0)
		{
			printf("figlio num: %d\n", i);
			while(1)
                usleep(10);
		}
		pid[i++] = temp_pid;
		usleep(100);
		printf("Ho creato il processo figlio: %d\n", temp_pid);
	}
	sleep(1);
	printf("Premi invio per chiudere i processi figli\n");
	i = 0;
	while (i < num_procs)
	{
		STEP
		if (kill(pid[i], SIGTERM) == -1)
			ft_exit_error(0, "Kill");
		printf("Killed: %d", pid[i]);
		i++;
	}
	printf("\nHo chuso tutti i processi figli\n");
	return (ft_exit(0));
}
	