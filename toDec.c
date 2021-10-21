#include <stdio.h>
#include <string.h>
#include <limits.h>
#define TAB_SIZE 8
#define BYTE 8
#define INT ((sizeof(char)*(BYTE)) * sizeof(int))
#define EXTRA_CHARS 3 //ADD [ ] ; INCR +3 CHARS OUTPUT PRINT

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
	{
		printf("|-----------------------------------------------------------help--------------------|\n");
		printf("|type: ./toDec test to view a simple test converter                                 |\n");
		printf("|type: ./toDec <a negative or positive number to convert> , accept multiple numbers | \n");
		printf("|-----------------------------------------------------------------------------------|\n");
		return 0;
	}
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
		if (len > (int)INT + EXTRA_CHARS)
			printf(" Out of range, limits: %ld bits\n", INT);
		else if (check(av[i]))
			printf("Bad argument\n");
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
