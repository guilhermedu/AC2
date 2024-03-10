#include <detpic32.h>
//ler os o valor do dip-switch de 4 bits (RB0 a RB3) e apresentá-lo no display de 7 segmentos (RD0 a RD6)
void delay(int ms);

int main(void){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    //reset
    LATB = (LATB & 0x80FF);
    LATD = (LATD & 0xFF9F);
    // configure RB0 to a RB3 as inputs
    TRISB = (TRISB | 0x000F);
    TRISB = (TRISB & 0x80FF);//out
    TRISD = (TRISD & 0xFF9F);//out
    // configure RD8 to RD14 and RD5 to RD6 as outputs
    LATD = (LATD | 0x0020); //RD5 = 1
    // Select display low
    while(1){
        //read dip-switch
        int index = PORTB & 0x000F;
        // covert to 7 segment code
        int num = display7Scodes[index];
        // send "num" to display
        LATB = num << 8;
    }
    return 0;
}


