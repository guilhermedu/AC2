#include <detpic32.h>

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}

int main()
{
    TRISE=TRISE & 0xFFC0;
    TRISB=TRISB | 0x0004;

    
}