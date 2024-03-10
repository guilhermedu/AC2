#include <detpic32.h>

void putc(char byte2send);
void putstr(char *s);

int main(void)
{
    U2BRG=((PBCLK+8*9600)/(9600*16))-1;
    U2MODEbits.BRGH=0;

    U2MODEbits.PDSEL=2;
    U2MODEbits.STSEL=1;

    U2STAbits.UTXEN=1;
    U2STAbits.URXEN=1;

    U2MODEbits.ON=1;

    IEC1bits.U2RXIE=1;
    IEC1bits.U2TXIE=0;

    IPC8bits.U2IP=2;
    IFS1bits.U2RXIF=0;

    EnableInterrupts();

    while(1);

    TRISB=TRISB | 0x000F;
    TRISE=TRISE & 0x0010;
    LATE=LATE & 0x0010;

    return 0;

}

void _int_(32) isr_uart2(void)
{
    if (IFS1bits.U2RXIF == 1){
        switch (U2RXREG)
        {
        case 'P':
            putstr("DipSwitch=");
            putc(PORTB & 0x0F);
            putc('\n');
            break;
        case 'T':
            LATE=LATE | 0x0010;
            break;
        default:
            break;
        }
        IFS1bits.U2RXIF = 0;
    }
}








void putc(char byte2send)
{
  while(U2STAbits.UTXBF == 1); // wait until buffer not full
    U2TXREG = byte2send;
}


void putstr(char *s) {
    while(*s != '\0') {
        putc(*s);
        s++;
    }
}




