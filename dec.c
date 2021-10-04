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
			return 1;
	return 0;
}

int main(int ac, char **av)
{
	int space = 0;
	
	if (ac < 2)
	{
		printf("Error arguments, enter number/s to converter\n");
		return 1;
	}
	int maxLen = 0;
	int len;
	for (int i = 0; i < ac; i++)
		if ((len = (int)strlen(av[i])) > maxLen)
			maxLen = len;
	maxLen +=3;
	printf("MAXLEN:%d\n", maxLen);
	for (int i = 1; i < ac ; i++)
	{
		long int ret = 0;
		if (check(av[i]))
		{
			printf("[%s]: Bad argument\n",av[i]);
			continue;
		}
		len = (int)strlen(av[i]);
		int tmp = len;
		len+=3;
		int c = -1;
		while (av[i][++c])
			ret += ((av[i][c] + 48 ) % 2) << (--tmp);
		printf("[%s]:", av[i]);
		while ((len/8) <= (maxLen /8))
		{
			len = len + 8;
			printf("\t");
		}
		printf("%ld\n", ret);

	}
	return 0;
}
