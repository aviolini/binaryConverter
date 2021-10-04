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
		int c = -1;
		while (av[i][++c])
		ret += ((av[i][c] + 48 ) % 2) << (--len);
		printf("[%s]:\t%ld\n", av[i], ret);
	}
	return 0;
}
