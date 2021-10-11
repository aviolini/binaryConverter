/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 09:38:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/09/21 00:35:41 by aviolini         ###   ########.fr       */
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

	if (ac != 2)
	{
		printf("Error arguments, enter the amount of numbers to display\n");
		return (1);
	}
	n = atoi(av[1]);
	if (n > MAX)
		return (printf("Error, limit is %d\n", MAX));
	numbers = (int *)malloc(sizeof(int) * n);
	srand((unsigned) time(&t));
	i = -1;
	while (++i < n)
	{
		num = rand() % MAX;
		numbers[i] = num;
		x = -1;
		while (++x < i)
			if (num == numbers[x])
				x = i--;
	}
	i = -1;
	while (++i < n)
		printf("%d ", numbers[i]);
	free(numbers);
	return (0);
}