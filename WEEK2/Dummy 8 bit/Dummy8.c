// Dummy for byte

#include "stdio.h"

int main()
{
	volatile short a = 0;
	volatile short b = 0;
	short i;

	for (i = 0; i < 7; i++) {
	  a = a + (a + 1);
	}
	b = a;
	
	printf("Resultado = %d \n",b);
	return 0;
}
