/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 11:51:47 by arrigo            #+#    #+#             */
/*   Updated: 2021/08/04 12:58:46 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int	main()
{
	printf("|sizeof:\n");
	printf("|\n");
	printf("|CHAR:");
	printf("\t\t%d\n",sizeof(char));
	printf("|MAX:");
	printf("%d\n", SCHAR_MAX);
	printf("|MIN:");
	printf("%d\n",SCHAR_MIN );
	printf("|___\n");
	printf("|\n");
	printf("|UNS_CHAR:");
	printf("\t%d\n",sizeof(unsigned char));
	printf("|MAX:");
	printf("%d\n", UCHAR_MAX);
	printf("|MIN:");
	printf("%d\n", 0);
	printf("|___\n");
	printf("|\n");
	printf("|SHORT:");
	printf("\t\t%d\n",sizeof(short));
	printf("|MAX:");
	printf("%d\n",SHRT_MAX );
	printf("|MIN:");
	printf("%d\n",SHRT_MIN );
	printf("|___\n");
	printf("|\n");
	printf("|UNS_SHORT:");
	printf("\t%d\n",sizeof(unsigned short));
	printf("|MAX:");
	printf("%d\n",USHRT_MAX );
	printf("|MIN:");
	printf("%d\n",0 );
	printf("|___\n");
	printf("|\n");
	printf("|INT:");
	printf("\t\t%d\n",sizeof(int));
	printf("|MAX:");
	printf("%d\n", INT_MAX);
	printf("|MIN:");
	printf("%d\n", INT_MIN);
	printf("|___\n");
	printf("|\n");
	printf("|UNS_INT:");
	printf("\t%d\n",sizeof(unsigned int));
	printf("|MAX:");
	printf("%u\n", UINT_MAX);
	printf("|MIN:");
	printf("%u\n", 0);
	printf("|___\n");
	printf("|\n");
	printf("|LONG:");
	printf("\t\t%d\n",sizeof(long));
	printf("|MAX:");
	printf("%ld\n",LONG_MAX );
	printf("|MIN:");
	printf("%ld\n",LONG_MIN );
	printf("|___\n");
	printf("|\n");
	printf("|UNS_LONG:");
	printf("\t%d\n",sizeof(unsigned long));
	printf("|MAX:");
	printf("%lu\n",ULONG_MAX );
	printf("|MIN:");
	printf("%ld\n",0 );
	printf("|___\n");
	printf("|\n");
	if (sizeof(long long) != sizeof(long))
	{		
		printf("|LONG LONG:");
		printf("\t%d\n",sizeof(long long));
		printf("|MAX:");
		printf("%lld\n",LLONG_MAX );
		printf("|MIN:");
		printf("%lld\n",LLONG_MIN );
		printf("|___\n");
		printf("|\n");
		printf("|UNS LONG LONG:");
		printf("\t%lld\n",sizeof(unsigned long long));
		printf("|MAX:");
		printf("%llu\n",ULLONG_MAX );
		printf("|MIN:");
		printf("%lld\n",0 );
		printf("|___\n");
		printf("|\n");
	}
	printf("|FLOAT:");
	printf("\t\t%d\n",sizeof(float));
	// printf("|MAX:");
	// printf("%d\n", );
	// printf("|MIN:");
	// printf("%d\n", );
	printf("|___\n");
	printf("|\n");
	printf("|DOUBLE:");
	printf("\t%d\n",sizeof(double));
	// printf("|MAX:");
	// printf("%d\n", );
	// printf("|MIN:");
	// printf("%d\n", );
	printf("|___\n");
	printf("|\n");
	printf("|LONG DOUBLE:");
	printf("\t%d\n",sizeof(long double));
	// printf("|MAX:");
	// printf("%d\n", );
	// printf("|MIN:");
	// printf("%d\n", );
	printf("|___\n");

	return(0);
}