#include<detpic32.h>

int main(void){
    unsigned char segment;
    //reset
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    //enable display low (RD5) and disable display high (RD6)
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    //configure RB8-RB14 as outputs
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    //configure RD5-RD6 as outputs

    while (1)
    {
        segment = 1;
        int i;
        for(i=0; i<7; i++){
            LATB = (LATB & 0x80FF) | (segment << 8);
            delay(500);
            segment = segment << 1;
        }
        LADbits.LATD5 = !LATDbits.LATD5;
        LADbits.LATD6 = !LATDbits.LATD6;
    }
    return 0;
}

    void delay(int ms){
        
        resetCoreTimer();
        while(readCoreTimer()<20000);
    
    }
