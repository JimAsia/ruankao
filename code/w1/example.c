#include<stdio.h>

int main(void)
{
	int max = 2147483647;
	unsigned u = -1;
	max = max + 1;
	printf( "max = %d\n", max );
	printf( "u = %u\n", u );
	printf( "%d\n", 5 / 2 );
	printf( "%f\n", 5.0 / 2 );
	printf( "%f\n", (double) 5 / 2 );

	return 0;
	
}