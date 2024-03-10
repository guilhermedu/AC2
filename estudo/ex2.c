#include <detpic32.h>

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000* ms);
}

int main()
{
    TRISE=TRISE & 0xFF87;
    TRISB=(TRISB | 0x0008);

    static double freq=5.2;

    int count=0;

    while(1) 
    {
        LATE=(LATE & 0xFF87) | count<<3;
        count++;

        if(count==12)
        {
            count=0;
        }

        int ds3=PORTBbits.RB3;

        if (ds3==1){
            freq=5.2;
        }else{
            freq=2.3;
        }
        
        double ms = (1000 / freq);

        delay((int)ms);
    }


}