#include <detpic32.h>

volatile int count=0;

void putc(char c);
char getc(void);
void putstr(char *str);

int main(void)
{
    //configuração dos portos
    TRISE=TRISE & 0xFFF0;

    //configuração da uart2
    U2BRG=(PBCLK + 8*9600)/(16*9600)-1;
    U2MODEbits.BRGH=0;
    U2MODEbits.PDSEL=0b10;
    U2MODEbits.STSEL=1;

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
    c= getc();
    putc(c);
    putc('\n');
    if(c=='F')
    {
        if(count==10)
        {
            count=0;
        }else{
            count++;
        }
        LATE=(LATE & 0xFFF0) | count;
    }else if((c=='C')) 
    {

        putstr("RESET");
        LATE=(LATE & 0xFFF0);
        putc('\n');
        count=0;
    }
}

void putc(char c)
{
    while(U2STAbits.UTXBF==1);
    U2TXREG=c;
}

char getc(void)
{
    while(U2STAbits.URXDA==0);
    return U2RXREG;
}

void putstr(char *str)
{
    int i;
    for(i=0;str[i]!= '\0';i++)
    {
        putc(str[i]);
    }
}
