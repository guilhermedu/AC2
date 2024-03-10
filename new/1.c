#include <detpic32.h>

void delay(int ms);

int main()
{
    TRISB=TRISB | 0x000F;

    TRISE=TRISE & 0xFFF0;
    LATE=LATE & 0xFFF0;

   

    while(1)
    {
        int count=0;
        count=count<<1;
        LATE=(LATE & 0xFFF0) | count;

        if(count== 32)
        {
            count=0;
            LATE=(LATE & 0xFFF0) | (PORTB ^ 0x000F);

        }
        delay(1000);  //1 hz
    }

}

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}