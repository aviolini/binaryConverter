/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toDec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:15:33 by arrigo            #+#    #+#             */
/*   Updated: 2022/02/10 11:50:06 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define TAB_SIZE 8
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))
#define EXTRA_CHARS 3 //ADD [ ] ; INCR +3 CHARS OUTPUT PRINT

int help()
{
	printf("|-----------------------------------------------------------help-----------------------------|\n");
	printf("|type: ./converterToDec test to view a simple test converter                                 |\n");
	printf("|type: ./converterToDec <a negative or positive number to convert> , accept multiple numbers |\n");
	printf("|--------------------------------------------------------------------------------------------|\n");
	return 0;
}

int check(char *s)
{
	int c = -1;
	while (s[++c])
	{
		if (s[c] != '1' && s[c] != '0')
			return 1;
	}
	return 0;
}
int main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Error arguments, enter number/s to converter\n");
		help();
		return 1;
	}
	int maxLen = 0;
	int len;
	for (int i = 0; i < ac; i++)
		if ((len = (int)strlen(av[i])) > maxLen)
			maxLen = len;
	maxLen += EXTRA_CHARS;	
	if (!strcmp(av[1],"test"))
	{
		char *new_av[] = {av[0], "011111111111111111111111111111111", "01111111111111111111111111111111",
						"01111111111111111111111111111110", "00000000000000010000000000000000",
						"00000000000000001000000000000000", "00000000000000000000000100000000",
						"00000000000000000000000010000000", "00000000000000000000000001000000",
						"00000000000000000000000000100000", "00000000000000000000000000010000",
						"00000000000000000000000000001000", "00000000000000000000000000000100",
						"00000000000000000000000000000010", "00000000000000000000000000000001",
						"00000000000000000000000000000000", "11111111111111111111111111111111",
						"11111111111111111111111111111110", "11111111111111111111111111111100",
						"11111111111111111111111111111000", "11111111111111111111111111110000",
						"11111111111111111111111111100000", "11111111111111111111111111000000",
						"11111111111111111111111110000000", "11111111111111111111111100000001",
						"11111111111111110111111111111111", "11111111111111101111111111111111",
						"10000000000000000000000000000000", NULL };
		ac = sizeof(new_av) / sizeof(char*) - 1;
		av = new_av;
	}
	if (!strcmp(av[1],"help"))
		return help();
	for (int i = 1; i < ac ; i++)
	{
		len = (int)strlen(av[i]);
		int index = len - 1;
		len += EXTRA_CHARS;
		printf("[%s]:", av[i]);
		int lenCopy = len;
		while ((len >> 3) <= (maxLen >> 3))				//	=/8
		{
			len = len + TAB_SIZE;
			printf("\t");
		}
		if (check(av[i]))
		{
			printf("Bad argument\n");
			help();
			return (2);
		}
		if (lenCopy > (int)INT + EXTRA_CHARS)
			printf("Out of range, limits: %ld bits\n", INT);
		else 
		{
			int c = 0;
			long ret = 0;
			while (av[i][c])
				ret += ((av[i][c++] + 48 ) % 2) << (index--);
			printf("%ld\n", ret);
		}
	}
	return 0;
}
