#include <detpic32.h>

volatile char count=0;

void putc(char c);
char getc(void);
void putstr(char *str);

int main(void)
{
    U2BRG=(PBCLK + 8*9600)/(9600*16)-1;
    U2MODEbits.BRGH=0;
    U2MODEbits.PDSEL=1;
    U2MODEbits.STSEL=0;
    U2STAbits.UTXEN=1;
    U2STAbits.URXEN=1;
    U2MODEbits.ON=1;

    IEC1bits.U2RXIE=1;
    IEC1bits.U2TXIE=0;
    IPC8bits.U2IP=1;

    EnableInterrupts();

    while(1);

    return 0;
}

void _int_(32) isr_uart2(void)
{
    
    char c;
    c=getc();
    if(c==islower(c))
    {
        count++;
    }
    if(c=='\n')
    {
        putstr("O número de minúsculas digitado foi");
        putc(count);
    }

}


void putc(char c)
{
    while(U2STAbits.UTXBF==1);
    c=U2RXREG;
}

char getc(void)
{
    while(U2STAbits.URXDA==0);
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
