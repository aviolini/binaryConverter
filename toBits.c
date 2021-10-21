/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toBits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:15:12 by arrigo            #+#    #+#             */
/*   Updated: 2021/10/21 19:15:13 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))
#define TAB_SIZE 8
#define EXTRA_CHARS 3

short is_neg;

int numlen(long n)
{
	int len = 0;
	for (; n > 0; n /= 10, len++){}
	return len;
}

void tab(long n, int maxLen)
{
	int len = numlen(n) + EXTRA_CHARS;
	while ((len >> 3) <= (maxLen >> 3))
	{
		len = len + TAB_SIZE;
		printf("\t");
	}
}

long int convert (long n, int space)
{
	int d = INT;
	if (n != 0)
	{
		(space)++;
		convert(n >> 1, space);
	}
	while (!n && (--d >= space))
	{
		if(!((d + 1) % BYTE))
			printf(" ");
		if (!is_neg)
			printf("0");
		else
			printf("1");
	}
	if (!n && !((d + 1) % BYTE))
		printf(" ");
	if (n)
	{
		printf("%ld", n % 2);
		(space)--;
		if(!(space % 8))
			printf(" ");
	}
	return 0;
}

int main(int ac, char **av)
{
	static int space = 0;
	if (ac < 2)
	{
		printf("Error arguments, enter number/s to converter\n");
		return 1;
	}
	if (!strcmp(av[1],"test"))
	{
		char *new_av[] = {av[0], "2147483648", "2147483647", "2147483646", "65536", "32768",
		"256", "128", "64", "32", "16", "8", "4", "2", "1", "0", "-1", "-2", "-4", "-8",
		"-16", "-32", "-64", "-128", "-255", "-32769", "-65537", "-2147483648", NULL};
		ac = sizeof(new_av) / sizeof(char*) - 1;
		av = new_av;
	}
	if (!strcmp(av[1],"help"))
	{
		printf("|-----------------------------------------------------------help--------------------|\n");
		printf("|type: ./toBits test to view a simple test converter                                |\n");
		printf("|type: ./toBits <a negative or positive number to convert> , accept multiple numbers| \n");
		printf("|-----------------------------------------------------------------------------------|\n");
		return 0;
	}
	int maxLen = 0;
	for (int i = 1; i < ac ; i++)
	{
		int c = 0;
		long n = atol(av[i]);
		for (; n > 0; n /= 10, c++){}
		if (c > maxLen)
			maxLen = c;
	}
	maxLen += EXTRA_CHARS;
	for (int i = 1; i < ac ; i++)
	{
		is_neg = 0;
		long n = atol(av[i]);
		if (n == 0 && strcmp(av[i], "0"))
		{
			printf("[%s]:", av[i]);
			tab(n, maxLen);
			printf(" Bad argument\n");
		}
		else if ( n > INT_MAX || n < INT_MIN)
		{
			printf("[%s]:", av[i]);
			tab(n, maxLen);
			printf(" Out of range, limits: [%d] and [%d]\n", INT_MAX, INT_MIN);
		}
		else 
		{
			printf("[");
			if (n < 0)
			{
				is_neg = 1;
				n *= -1;
				printf("-");
			}
			printf("%ld]:", n);
			tab(n, maxLen);
			if (is_neg)
				n = (-n + UINT_MAX + 1);
			convert(n, space);
			printf("\n");
		}
	}
	return 0;
}
