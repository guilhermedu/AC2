#include <detpic32.h>

void putc(char byte2send);



int main(void)
{
    //configurar porto RC14
    TRISC = TRISC  & 0xBFFF;// configure port C14 (output)
    LATC = LATC & 0xBFFF; // set port C14 to 0
    // Configure UART2: 115200, N, 8, 1
    U2BRG = ((PBCLK + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0; // 16
    U2MODEbits.PDSEL = 0; // 8 bits, no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.UTXEN = 1; // Enable UART transmitter
    U2STAbits.URXEN = 1; // Enable UART receiver
    U2MODEbits.ON = 1; // Enable UART2

    // Configure UART2 Interrupts, with RX interrupts enabled and TX interrupts disabled
    IEC1bits.U2RXIE = 1; // Enable UART2 RX interrupts
    IEC1bits.U2TXIE = 0; // Disable UART2 TX interrupts

    //set UARt2 priority level (register IPC8)
    IPC8bits.U2IP = 1; // Priority 1
    //clear UARt2 interrupt flag (register IFS1)
    IFS1bits.U2RXIF = 0; // Reset UART2 RX interrupt flag
    //define RX interrupt priority (URXISEL bits)
    U2STAbits.URXISEL = 0; // Interrupt is generated when any character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more characters.

    EnableInterrupts(); // Global Interrupt Enable

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