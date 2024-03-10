#include <detpic32.h>

volatile int count=15;

void putc(char c);
char getc(void);
void putstr(char *str);

int main(void)
{
    TRISE=TRISE & 0xFFE1;

    //configuração da uart2
    U2BRG=(PBCLK + 8 *9600)/(16*9600)-1;
    U2MODEbits.BRGH=0;
    U2MODEbits.PDSEL=1;
    U2MODEbits.STSEL=1;

    U2STAbits.UTXEN=1;
    U2STAbits.URXEN=1;
    U2MODEbits.ON=1;

    IEC1bits.U2RXIE=1;
    IEC1bits.U2TXIE=0;
    IPC8bits.U2IP=1;

    EnableInterrupts();

    while(1);
}

void _int_(32) _isr_uart2(void)
{
    char c;
    c=getc();
    putc(c);
    putc('\n');
    if(c=='U')
    {
        LATE=(LATE & 0xFFE1)| count >>1;
        count--;
    }
    else if(c=='R' || count==0)
    {
        putstr("RESET");
        putc('\n');
        count=15;
    }
}

void putc(char c)
{
    U2STAbits.UTXBF==1;
    U2TXREG=c;
}

char getc(void)
{
    U2STAbits.URXDA==0;
    return U2RXREG;
}


void putstr(char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
    {
        putc(str[i]);
    }
}



