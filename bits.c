#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))

long int convert (int n, int *space)
{
	int d = INT;
	if (n != 0)
	{
		(*space)++;
		convert(n >> 1, space);
	}
	while (!n && (--d > *space))
	{
		if(!(d % BYTE))
			printf(" ");
		printf("0");
	}
	if (!n && !(d%BYTE))
		printf(" ");
	if (n)
	{
		printf("%ld", n % 2);
		(*space)--;
		if(!(*space % 8))
			printf(" ");
	}
	return 0;
}

int main(int ac, char **av)
{
	int space = 0;
	if (ac < 2)
	{
		printf("Error arguments\n");
		return 1;
	}
	for (int i = 1; i < ac ; i++)
	{
		long int n = atol(av[i]);
		if (n < INT_MIN || n > INT_MAX)
		{
			printf("Bad argument\n");
			return 1;
		}
		printf("[%d]:\t");
		convert((int)n, &space);
		printf("\n");
	}
	return 0;
}
