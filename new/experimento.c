#include <detpic32.h>

void putc(char c);
void putstr(char *s);

int main(void)
{
    U2BRG=((PBCLK+8*9600)/(16*9600))-1;
    U2MODEbits.BRGH=0;
    U2MODEbits.PDSEL=2;
    U2MODEbits.STSEL=1;//2 stop bits
    U2STAbits.URXEN=1; //enable reception
    U2STAbits.UTXEN=1;//enable transmition
    U2MODEbits.ON=1;

    //UART2 Rx interrupts
    U2STAbits.URXISEL=0;
    IEC1bits.U2RXIE=1;
    IFS1bits.U2RXIF=0;
    IPC8bits.U2IP=2;

    //configurar portos
    TRISB=TRISB | 0x0F;
    TRISE=TRISE & 0xFFEF;

    LATEbits.LATE4=1;

    EnableInterrupts();

    while(1);

    return 0;

}

void _int_(32) isr_uart2(void)
{
    if(IFS1bits.U2RXIF == 1)
    {
        switch (U2RXREG)
        {
        case 'P':
            putstr("DipSwitch=");
            putc(PORTB & 0x0F);
            putc('\n');
            break;
        case 'T':
            LATEbits.LATE4= ! LATEbits.LATE4;
            break;
        default:
            break;
        }
        IFS1bits.U2RXIF == 0;
    }

}

void putc(char c)
{
    while(U2STAbits.UTXBF == 1);
    U2TXREG = c;

}

void putstr(char *s)
{
    while(*s != '\0'){
        putc(*s);
        s++;
    }
}
