#include <detpic32.h>

void putc(byte2send);
void putstrInt(char *s);

typedef struct{
    char mem[100];  // Storage area
    int nchar;      // Number of characters to be transmitted
    int posrd;      // Position of the next character to be transmitted
} t_buf;

volatile t_buf txbuf;

int main()
{
    U2BRG=((PBCLK + 8 *9600)/(9600 *16))-1;

    U2MODEbits.BRGH=0;

    U2MODEbits.PDSEL=1;//even parity
    U2MODEbits.STSEL=0;//1 Stop bit

    U2STAbits.UTXEN=1;
    U2STAbits.URXEN=1;

    U2MODEbits.ON=1;

    IEC1bits.U2RXIE=1;
    IEC1bits.U2TXIE=0;

    IPC8bits.U2IP=1;

    IFS1bits.U2RXIF=1;

    EnableInterrupts();

    while(1);

    return 0;


}

void _int_ (32) isr_uart2(void)
{
    char read= U2TXREG;
    putc(read);
    int count=0;
    while(read !='\n')
    {
        if(islower(read))
        {
            count++;
        }

    }
    //char count_str[20];

    putstrInt("O número de letras minúsculas é:");
    //escrever o count logo a seguir ta foda
    printf(count,10 | 2<<16);

    return 0;
}




void putc(byte2send)
{
    while(U2STAbits.UTXBF==1);
    U2TXREG=byte2send;
}



void putstrInt(char *s){
    while(txbuf.nchar > 0); // Wait while the buffer is not empty
    // Copy all characters of the string "s" to the buffer
    while(*s != '\0') {
        txbuf.mem[txbuf.nchar] = *s;
        s++;
        txbuf.nchar++;
    }
    // Initialize "posrd" variable with 0
    txbuf.posrd = 0;
    // Enable UART2 Tx interrupts
    IEC1bits.U2TXIE = 1; 
}
