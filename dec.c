#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))

int check(char *s)
{
	int c = -1;
	while (s[++c])
		if (s[c] != '1' && s[c] != '0')
		{
			printf("Bad argument\n");
			return 1;
		}
	return 0;
}

long int convert (int n, int space)
{
	long int ret = 0;
	if (n != 0)
		ret = convert(n / 10, ++space);
	if (n)
		ret += (n % 2) << (space--);
	return ret;
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
		long int ret = 0;
		size_t size = strlen(av[i]);
		if (check(av[i]))
			continue;
		printf("ok\n");

		// printf("[%ld]:\t", n);
		// if (n < 0)// || n > INT_MAX) // || n < INT_MIN TODO
		// {
		// 	printf("Bad argument\n");
		// 	return 1;
		// }
		// ret = convert((int)n, space);
		// // if (!n)
		// 	printf("%d\n", ret);
		// // printf("\n");
	}
	return 0;
}
