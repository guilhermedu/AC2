#include <detpic32.h>

void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
    
}

int main(void)
{
    //reset
    LATCbits.LATC14 = 0;
    // Configure port RC14 as output
    TRISCbits.TRISC14 = 0;

    while(1)
    {
        //wait 0.5s
        delay(500);
        //Toggle RC14 port value
        LATCbits.LATC14 = !LATCbits.LATC14;
        //LATC= LATC ^ 0x4000;//0100 0000 0000 0000
    }
    return 0;
}

