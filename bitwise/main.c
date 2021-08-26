
#include <stdio.h>

int main()
{
	int n = 1;
	printf("n=%d\n", n);
	printf("n<<0 = %d\tn<<1 = %d\tn<<2 = %d\tn<<3 = %d\tn<<4 = %d\tn<<5 = %d\tn<<6 = %d\tn<<7 = %d\tn<<8 = %d\n", \
		n<<0,n<<1,n<<2,n<<3,n<<4,n<<5,n<<6,n<<7,n<<8);
	
	printf("\n");
	n = 256;
	printf("n=%d\n", n);
	printf("n>>0 = %d\tn>>1 = %d\tn>>2 = %d\tn>>3 = %d\tn>>4 = %d\tn>>5 = %d\tn>>6 = %d\tn>>7 = %d\tn>>8 = %d\n", \
		n>>0,n>>1,n>>2,n>>3,n>>4,n>>5,n>>6,n>>7,n>>8);
	
	
	printf("\n~1 = %d\t\t~0 = %d\n",~1,~0);
	printf("1&1 = %d\t\t1&0 = %d\t\t0&0 = %d\n",1&1,1&0,0&0);
	printf("1|1 = %d\t\t1|0 = %d\t\t0|0 = %d\n",1|1,1|0,0|0);
	printf("1^1 = %d\t\t1^0 = %d\t\t0^0 = %d\n",1^1,1^0,0^0);
	return 0;
}
