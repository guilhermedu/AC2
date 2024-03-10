#include <detpic32.h>

void delay(int ms);

int main()
{
    TRISB=TRISB | 0xFFE1;

    int count=0b00000000;

    while(1)
    {
        count=(count<<1) | ~ (PORTB = PORTB ^ 0x001E);
        count++;
    }
    delay(1000);

   
}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()< 20000 * ms);
}
