#include <detpic32.h>

void delay(int ms);

int main(void)
{
    //Ports
    TRISD=TRISD | 0x0100; // 0000 0001 0000 0000
    TRISE=TRISE & 0xFFFE; // 1111 1111 1111 1110

    while(1)
    {
        LATE = (LATE & 0xFFFE);
        if(!((PORTD & 0x0100)==0x0100)){
            LATE = (LATE & 0xFFFE) | 0x0001;
            delay (3000);
        }
    }
    return 0;

}
// função delay
void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms );

}