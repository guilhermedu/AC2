#include<detpic32.h>

void delay(int ms )
{
    resetCoreTimer();
    while(readCoreTimer()<200000*ms);
}

int main()
{
    //configuração de portos saída
    TRISE=TRISE & 0xFFC0;
    //configuração de porto de entrada RB2
    TRISB=TRISB | 0x0004;

    static double freq=7;

    unsigned int padrao=0b000001;

    while (1)
    {
        LATE=(LATE & 0xFFC0) | padrao;

        padrao=padrao<<1;

        if(padrao==0b100000)
        {
            padrao=0b000001;
        }
        int ds3= PORTBbits.RB2;
        if(ds3=1){
            freq=7;
        }else{
            freq=3;
        }
        double ms = 1000 / freq;

        delay((int) ms);
    }
    return 0;
     
}
