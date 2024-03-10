#include <detpic32.h>

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}

int main()
{
    TRISE=(TRISE & 0xFFE0);
    TRISB=(TRISB | 0x0004);

    static double freq = 7;

    unsigned int padrao = 0b000001;

    while(1)
    {
        LATE=(LATE & 0xFF03)  | padrao<<2;

        padrao=padrao<<1;

        if(padrao==0b100000) padrao=0b000001;

        int ds2= PORTBbits.RB2;

        if(ds2==1)freq=7;
        else if(ds2==0)freq==3;

        double ms=1000.0/freq;

        double((int) ms);
    }
    return 0;
}