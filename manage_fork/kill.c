/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_kill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:14:30 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/05 11:23:43 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h> 

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
	int wstatus;

	i = 0;
	num_procs = 5;
	while (i < num_procs)
	{
		temp_pid = fork();
		if (temp_pid == -1)
			ft_exit_error(0, "Fork");
		if (temp_pid == 0)
		{
			printf("%d:figlio num %d\n",getpid(), i);
			while(1)
                usleep(10);
		}
		pid[i++] = temp_pid;
		usleep(100);
	}
	sleep(1);
	printf("Premi invio per chiudere i processi figli\n");
	i = 0;
	while (i < num_procs)
	{
		STEP
		if (kill(pid[i], SIGTERM) == -1)
			ft_exit_error(0, "Kill");
		printf("%d:Killed\n", pid[i]);
		if (waitpid(pid[i], &wstatus, 0) == -1)
			ft_exit_error(0, "Waitpid");
		if (WIFEXITED(wstatus))
			printf("%d:E' terminato normalmente, con exit_status: %d\n", pid[i], WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
				printf("%d:E' terminato con il segnale: %d\n", pid[i], WTERMSIG(wstatus));
		i++;
	}
	printf("\nHo chuso tutti i processi figli\n");
	return (ft_exit(0));
}
	