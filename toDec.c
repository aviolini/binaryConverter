#include <stdio.h>
#include <string.h>
#define TAB_SIZE 8
#define EXTRA_CHARS 3 //ADD [ ] ; INCR +3 CHARS OUTPUT PRINT

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
	maxLen += EXTRA_CHARS;	
	for (int i = 1; i < ac ; i++)
	{
		len = (int)strlen(av[i]);
		int index = len - 1;
		len += EXTRA_CHARS;
		printf("[%s]:", av[i]);
		while ((len>>3) <= (maxLen>>3))				//	=/8
		{
			len = len + TAB_SIZE;
			printf("\t");
		}
		if (check(av[i]))
			printf("Bad argument\n");
		else 
		{
			int c = 0;
			long int ret = 0;
			while (av[i][c])
				ret += ((av[i][c++] + 48 ) % 2) << (index--);
			printf("%ld\n", ret);
		}
	}
	return 0;
}
