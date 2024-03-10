#include <detpic32.h>

int main()
{
    //configuração da UART2
    U2BRG=(((PBCLK+8*9600))/(16*9600))-1;
    U2MODEbits.BRGH=0;//16
    U2MODEbits.PDSEL=2;//8 bits,odd parity
    U2MODEbits.STSEL=1; // 2 stop bits

    U2STAbits.UTXEN=1; // Enable UART transmitter
    U2STAbits.URXEN=1; // Enable UART receiver

    U2MODEbits.on=1; //Enable UART2

    
}