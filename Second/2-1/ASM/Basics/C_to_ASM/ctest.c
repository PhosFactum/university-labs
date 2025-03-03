#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int16_t var = 3;
int16_t var1;
int16_t result;

extern int asmfunc(void);

int main (void)
{
	result = asmfunc();
	printf("Hello: res = %d, var1 = %d\n", result, var1);
	return 0;
}
