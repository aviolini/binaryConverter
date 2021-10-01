#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))

long int convert (int n, int space, int *ret)
{
	// long int ret = 0;
	if (n != 0)
		convert(n / 10, ++space, ret);
	if (n)
		*ret += (n % 2) << (space--);
	return 0;
}

int main(int ac, char **av)
{
	static int space = -1;
	
	if (ac < 2)
	{
		printf("Error arguments, enter number/s to converter\n");
		return 1;
	}
	for (int i = 1; i < ac ; i++)
	{
		int ret = 0;
		long int n = atol(av[i]);
		printf("[%ld]:\t", n);
		if (n < 0 || n > INT_MAX) // || n < INT_MIN TODO
		{
			printf("Bad argument\n");
			return 1;
		}
		convert((int)n, space, &ret);
		// if (!n)
			printf("%d\n", ret);
		// printf("\n");
	}
	return 0;
}
