#include <detpic32.h>


void putc(char byte);
char getc(void);

int main()
{
    // Configure UART2:
    // 1 - Configure BaudRate Generator
    U2BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0; // divisao por 16
    // 2 - Configure number of data bits, parity and number of stop bits
    // (see U1MODE register)
    U2MODEbits.PDSEL = 1; // 8 bits sem paridade
    U2MODEbits.STSEL = 0; // 1 stop bit
    // 3 - Enable the transmitter and receiver modules (see register U1STA)
    U2STAbits.UTXEN = 1; // transmissao
    U2STAbits.URXEN = 1; // rececao
    // 4 - Enable UART2 (see register U1MODE)
    U2MODEbits.ON = 1; // ativar UART2

    while(1)
    {
        // Read character using getc()
        // Send character using putc()
        char g=getc();
        putc(g);
         
    }
}


void putc(char byte)
{
    // wait while UART2 UTXBF ==1
    while(U2STAbits.UTXBF == 1);
    // Copy byte to the UxTXREG register
    U2TXREG = byte;
}

char getc(void)
{
    //wait while URXDA == 0
    while(U2STAbits.URXDA == 0);
    // Return U1RXREG
    return U2RXREG;
}






