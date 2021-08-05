/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_sig-handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:14:30 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/05 11:22:42 by arrigo           ###   ########.fr       */
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
		pid[i] = temp_pid;
		sleep(1);
		// wait(NULL);
		i++;
	}
	sleep(1);
	i = 0;
	while (i < num_procs)
	{
		if (i == 0)
		{
			if (kill(pid[i], SIGSTOP) == -1)
				ft_exit_error(0, "Kill");
			printf("%d:Stopped\n",pid[i]);
			sleep(1);
			if (kill(pid[i], SIGCONT) == -1)
				ft_exit_error(0, "Kill");
			printf("%d:Continue\n",pid[i]);
		}
		if (kill(pid[i], SIGTERM) == -1)
			ft_exit_error(0, "Kill");
		printf("%d:Killed\n", pid[i]);
		if (waitpid(pid[i], &wstatus, 0) == -1)
			ft_exit_error(0, "Waitpid");
		if (WIFEXITED(wstatus))
			printf("%d:E' terminato normalmente, con exit_status: %d\n", pid[i], WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
				printf("%d:E' terminato con il segnale: %d\n", pid[i], WTERMSIG(wstatus));
		sleep(1);
		i++;
	}
	printf("\nHo chuso tutti i processi figli\n");
	return (ft_exit(0));
}
	