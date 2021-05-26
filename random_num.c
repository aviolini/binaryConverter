/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 09:38:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/26 13:14:56 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 1000

int main (int ac, char **av)
{
 	int		i, n, num, x;
   	time_t	t;
	int		*numbers;
	
	x = -1;
	i = -1;
	if (ac != 2)
		return (0);
	n = atoi(av[1]);
	if (n > MAX)
		return (printf("Error, limit is %d\n", MAX));
	numbers = (int *)malloc(sizeof(int) * n);
	srand((unsigned) time(&t));
	while (++i < n)
	{
		num = rand() % MAX;
		numbers[i] = num;
		x = -1;
		while (++x < (i))
		{
			if (num == numbers[x])
			{
				i--;
				break ;
			}
		}
	}
	i = -1;
	while (++i < n)
	{
		printf("%d ", numbers[i]);
	}
	free(numbers);
	return (1);
}