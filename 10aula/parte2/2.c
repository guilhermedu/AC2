#include <detpic32.h>

void putc(char byte);
void delay(int ms);

int main(void)
{
    //Configure UART2:
    //1-Configure BaudRate Generator
    U1BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
    U1MODEbits.BRGH = 0; //divisao por 16
    //2-Configure number of data bits, parity and number of stop bits
    // (see U1MODE register)
    U1MODEbits.PDSEL = 0; //8 bits sem paridade
    U1MODEbits.STSEL = 0; //1 stop bit
    //3-Enable the transmitter and receiver modules (see register U1STA)
    U1STAbits.UTXEN = 1; //transmissao
    U1STAbits.URXEN = 1; //rececao
    //4-Enable UART2 (see register U1MODE)
    U1MODEbits.ON = 1; //ativar UART2

    while(1)
    {
        putc1(0x5A);
        delay(1000);
    }

}

void putc1(char byte)
{
    // wait while UART2 UTXBF ==1
    while(U1STAbits.UTXBF == 1);
    // Copy byte to the UxTXREG register
    U1TXREG = byte;
}

//função delay
void delay(int ms)
{
    
    resetCoreTimer();
    while(readCoreTimer() < 20000*ms);
    
}