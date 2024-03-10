#include <detpic32.h>

void putc(char byte2send);



int main(void)
{
    TRISE = TRISE & 0xFFE1; // Configure port E as output
    LATE = LATE & 0xFFE1;   // Set port E to 0
    
    // Configure UART2: 115200, N, 8, 1
    U2BRG = ((PBCLK + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0; // 16
    U2MODEbits.PDSEL = 0; // 8 bits, no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.UTXEN = 1;  // Enable UART transmitter
    U2STAbits.URXEN = 1;  // Enable UART receiver
    U2MODEbits.ON = 1;    // Enable UART2

    // Configure UART2 Interrupts
    IEC1bits.U2RXIE = 1;  // Enable UART2 RX interrupts
    IEC1bits.U2TXIE = 0;  // Disable UART2 TX interrupts

    // Set UART2 priority level
    IPC8bits.U2IP = 1;    // Priority 1

    // Clear UART2 RX interrupt flag
    IFS1bits.U2RXIF = 0;

    EnableInterrupts();   // Global Interrupt Enable

    while (1);

    return 0;
}

void _int_(32) isr_uart2(void)
{
    char read = U2RXREG;
    putc(read);

    static unsigned int counter = 14;
    
    
    
        if (read == 'U') {
            counter = (counter + 1) % 16;

            LATEbits.LATE4 = (counter & 0x08) >> 3;  // LED RE4
            LATEbits.LATE3 = (counter & 0x04) >> 2;  // LED RE3
            LATEbits.LATE2 = (counter & 0x02) >> 1;  // LED RE2
            LATEbits.LATE1 = counter & 0x01;         // LED RE1
        }

        if (read == 'R') {
            
            
            counter = 0;
            printf("RESET");
                    
        }
    
    
  
        
}

void putc(char byte2send)
{
    while (U2STAbits.UTXBF == 1); // Wait while UTXBF == 1
    U2TXREG = byte2send;          // Copy byte2send to the UxTXREG register
}


