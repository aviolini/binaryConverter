#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))
#define TAB_SIZE 8
#define EXTRA_CHARS 3

int numlen(int n)
{
	int len = 0;
	for (; n > 0; n /= 10, len++){}
	return len;
}

void tab(int n, int maxLen)
{
	int len = numlen(n) + EXTRA_CHARS;
	while ((len>>3) <= (maxLen>>3))
	{
		len = len + TAB_SIZE;
		printf("\t");
	}
}

long int convert (int n, int space)
{
	int d = INT;
	if (n != 0)
	{
		(space)++;
		convert(n >> 1, space);
	}
	while (!n && (--d > space))
	{
		if(!(d % BYTE))
			printf(" ");
		printf("0");
	}
	if (!n && !(d%BYTE))
		printf(" ");
	if (n)
	{
		printf("%d", n % 2);
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
	int maxLen = 0;
	for (int i = 1; i < ac ; i++)
	{
		int c = 0;
		long int n = atol(av[i]);
		for (; n > 0; n /= 10, c++){}
		if (c > maxLen)
			maxLen = c;
	}
	maxLen += EXTRA_CHARS;
	for (int i = 1; i < ac ; i++)
	{
		long int n = atol(av[i]);
		if (n < 0 || n > INT_MAX || (n == 0 && strcmp(av[i], "0"))) // n < 0 TODO
		{
			printf("[%s]:", av[i]);
			tab(n, maxLen);
			printf("Bad argument\n");
		}
		else 
		{
			printf("[%ld]:", n);
			tab(n, maxLen);
			convert((int)n, space);
			printf("\n");
		}
	}
	return 0;
}
