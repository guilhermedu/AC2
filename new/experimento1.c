#include <detpic32.h>

void putc(char c);
void putstr(char *s);

int main(void)
{
    U2BRG = ((PBCLK + 8 * 9600) / (16 * 9600)) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 1;//even parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    U2STAbits.URXISEL = 0;
    IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;
    IPC8bits.U2IP = 2;

    EnableInterrupts();

    int count = 0;

    while (1)
    {
        if (U2STAbits.URXDA == 1)
        {
            char received = U2RXREG;
            putc(received);

            if (received >= 'a' && received <= 'z')
                count++;
            
            if (received == '\n')
            {
                putstr("O número de minúsculas é: ");
                putc(count + '0');
                putc('\n');
                count = 0;
            }
        }
    }

    return 0;
}

void putc(char c)
{
    while (U2STAbits.UTXBF == 1);
    U2TXREG = c;
}

void putstr(char *s)
{
    while (*s != '\0')
    {
        putc(*s);
        s++;
    }
}
