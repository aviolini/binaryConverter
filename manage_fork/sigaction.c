/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:14:30 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/05 16:02:16 by arrigo           ###   ########.fr       */
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

void ft_sigterm(int sig)
{
	printf("%d:Ricevuto il segnale SIGTERM:%d\n",getpid(),sig);
	if ((signal(sig, SIG_DFL)) == SIG_ERR) //SERVE A SBLOCCARE IL SEGNALE
		ft_exit_error(0, "Signal");
	if (kill(getpid(), sig) == -1)
		ft_exit_error(0, "Kill");
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
			if (signal(SIGTERM, ft_sigterm) == SIG_ERR)
				ft_exit_error(0, "Signal");
			if (signal(SIGINT, SIG_DFL) == SIG_ERR)
				ft_exit_error(0, "Signal");
			if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
				ft_exit_error(0, "Signal");
			if (signal(SIGUSR1, SIG_IGN) == SIG_ERR)
				ft_exit_error(0, "Signal");
			while(1);
		}
		pid[i] = temp_pid;
		sleep(0.1);
		// wait(NULL);
		i++;
	}
	sleep(1);
	i = 0;
	while (i < num_procs)
	{
		if (i == 0)
		{
			if (kill(pid[i], SIGSTOP) == -1)		// LIKE CTRL-Z IN BASH
				ft_exit_error(0, "Kill");
			printf("%d:Stopped\n",pid[i]);
			sleep(1);
			if (kill(pid[i], SIGCONT) == -1)		//LIKE fg IN BASH
				ft_exit_error(0, "Kill");
			printf("%d:Continued\n",pid[i]);
			if (kill(pid[i], SIGKILL) == -1)
				ft_exit_error(0, "Kill");
		usleep(1000);
		}
		else if (i == 1)
		{	
			if (kill(pid[i], SIGINT) == -1)
				ft_exit_error(0, "Kill");
			usleep(1000);
		}
		else if (i == 2)
		{	
			if (kill(pid[i], SIGTERM) == -1)
				ft_exit_error(0, "Kill");
			usleep(1000);
		}
		else if (i == 3)
		{	
			if (kill(pid[i], SIGQUIT) == -1)
				ft_exit_error(0, "Kill");
			usleep(1000);
		}
		else
			if (kill(pid[i], SIGKILL) == -1)
				ft_exit_error(0, "Kill");
		if (waitpid(pid[i], &wstatus, 0) == -1)
			ft_exit_error(0, "Waitpid");
		printf("%d:Killed\n", pid[i]);
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
	