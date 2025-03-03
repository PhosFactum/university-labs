#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // for int16_t

int16_t var_init = 15;
int16_t var_asm;
int16_t result;

extern int asmfunc();

int main()
{
    result = asmfunc();
    printf("Answer is: result = %d, var_temp = %d...", result, var_asm);
    return 0;
}
