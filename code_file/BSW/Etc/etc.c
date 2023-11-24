#include "etc.h"

// init_gpt1() should be called before using delay_ms()
void delay_ms(unsigned int delay_time)
{
    volatile unsigned int i, j;
    for(i=0; i<delay_time; i++)
        for(j=0; j<18200; j++)
            continue;
}


