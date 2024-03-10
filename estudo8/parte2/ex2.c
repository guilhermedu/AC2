#include <detpic32.h>

int main(void)
{
    //configure ports,Timer T2,interrupts and external interrupt INT1
    TRISD=TRISD | 0x0100;
    TRISE=TRISE & 0xFFFE;

    T2CONbits.TCKPS = 7; // Configure Timers T2 with interrupts enabled)  //2hz/ 2 = 1hz/3 = 0.3hz 
    PR2 = 39063; 
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    IPC1bits.INT1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.INT1IE = 1; // Enable timer T2 interrupts
    IFS0bits.INT1IF = 0; // Reset timer T2 interrupt flag

    INTCONbits.INT1EP =0; // INT1 config

    EnableInterrupts();  //global interrupt Enable

    while(1);

    return 0;
}

void _int_(8) isr_T2(void){
    static int count = 0;

    LATE=(LATE & 0xFFFE) | 0x0001;

    if(count % 6==0)
    {
        IEC0bits.T2IE = 0;
        LATE = (LATE & 0xFFFE); // turns of led
        putchar('c');
    }
    IFS0bits.T2IF = 0;

}
void _int_(7) isr_INT1(void)
{
    IPC2bits.T2IP = 1;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    putchar('b');

    //waits for another push on int1
    IFS0bits.INT1IF = 0;
}