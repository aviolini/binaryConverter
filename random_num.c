/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 09:38:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/27 07:22:23 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 10

int main (int ac, char **av)
{
 	int		i, n, num, x;
   	time_t	t;
	int		*numbers;

	if (ac != 2)
		return (1);
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