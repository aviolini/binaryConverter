/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_waitpid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:14:30 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/05 11:24:02 by arrigo           ###   ########.fr       */
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
	int pid[5];
	int temp_pid;
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
           	sleep(1+i);
			if (i == 0)
				exit(0);					//ESCE SENZA ERRORI
			if (i == 1)
				exit(1);					//ESCE CON ERRORE
			if (i == 2)
				if (kill(getpid(), SIGTERM) == -1)	//ESCE CON AUTO-TERM
					ft_exit_error(0, "Kill");
			if (i == 3)
				if (kill(getpid(), SIGKILL))	//ESCE CON AUTO-KILL
					ft_exit_error(0, "Kill");
			exit(0);
		}
		pid[i++] = temp_pid;
		usleep(100);
		printf("Ho creato il processo figlio: %d\n", temp_pid);
	}
	sleep(1);
	printf("Aspetto che finiscano i processi figli\n");
	i = 0;
	while (i < num_procs)
	{
		if (waitpid(pid[i], &wstatus, 0) == -1)
			ft_exit_error(0, "Waitpid");
		if (WIFEXITED(wstatus))
			printf("%d:E' terminato normalmente, con exit_status: %d\n", pid[i], WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
				printf("%d:E' terminato con il segnale: %d\n", pid[i], WTERMSIG(wstatus));
		i++;
	}
	printf("Ho aspettato tutti i processi figli\n");
	return (ft_exit(0));
}
	