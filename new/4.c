#include <detpic32.h>

void putc(char byte2send);

int main(void)
{
    //configurar porto RC14
    TRISC=TRISC & 0xBFFF;// configure port C14 (output)
    LATC=LATC & 0xBFFF; // set port C14 to 0
    //Configure UART2: 115200, N, 8, 1
    U2BRG = ((PBCLK + 8 * 115200 )/ (16 * 115200))-1;
    U2MODEbits.BRGH=0; //16
    U2MODEbits.PDSEL=0; // 8 bits, no parity
    U2MODEbits.STSEL=0; // 1 stop bit
    U2STAbits.UTXEN=1; // Enable UART transmitter
    U2STAbits.URXEN=1;// Enable UART receiver
    U2MODEbits.ON=1; // Enable UART2

    //Configure UART2 Interrupts, with RX interrupts enabled
    IEC1bits.U2RXIE = 1 ; // Enable UART2 RX interrupts
    IEC1bits.U2TXIE = 0; // Reset UART2  Tx interrupts

    IPC8bits.U2IP = 1; // priority 1
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;

    EnableInterrupts(); // global Interrupt Enable

    while(1);

    return 0;
}

void _int_(32) isr_uart2(void)
{
    char read;
    read=U2RXREG;
    if(read == 'T')
    {
        LATC= (LATC & 0xBFFF)| 0x4000;
    }
    if(read == 't')
    {
        LATC= (LATC  & 0xBFFF)| 0x0000;
    }
    putc(read);
    IFS1bits.U2RXIF = 0; // Reset UART2 RX interrupt flag
}

void putc(char byte2send)
{
    while(U2STAbits.UTXBF == 1); // Wait while UTXBF == 1
    U2TXREG = byte2send; // Copy byte2send to the UxTXREG register
}