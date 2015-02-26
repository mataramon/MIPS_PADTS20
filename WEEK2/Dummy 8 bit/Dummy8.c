// Dummy for byte

#include "stdio.h"

int main()
{
	volatile char a = 0;
	volatile unsigned char b = 0;
	short i;

	for (i = 0; i < 10; i++) {
	  a = a + (a + 1);
	}
	b = a;
	
	printf("Resultado = %d \n",b);
	return 0;
}
