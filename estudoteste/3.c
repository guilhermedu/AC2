#include <detpic32.h>

void putc(char byte2send);
void putstr(char *s);
int main(void)
{
    
    

    //Port
    TRISE = TRISE & 0xFFE1;
    LATE= LATE & 0xFFE1;
    
    // Configure UART2: 9600, N, 8, 1
    U2BRG = ((PBCLK + 8 * 9600) / (16 * 9600)) - 1;
    U2MODEbits.BRGH = 0; // 16
    U2MODEbits.PDSEL = 2; // 8 bits, odd parity
    U2MODEbits.STSEL = 1; // 2 stop bit

    U2STAbits.UTXEN = 1; // Enable UART transmitter
    U2STAbits.URXEN = 1; // Enable UART receiver
    
    U2MODEbits.ON = 1; // Enable UART2

    // Configure UART2 Interrupts
    IEC1bits.U2RXIE = 1;  // Enable UART2 RX interrupts
    IEC1bits.U2TXIE = 0;  // Disable UART2 TX interrupts

    // Set UART2 priority level
    IPC8bits.U2IP = 1;    // Priority 1

    // Clear UART2 RX interrupt flag
    IFS1bits.U2RXIF = 0;

    EnableInterrupts();

    while(1);

    return 0; 
}

void _int_(32) isr_uart2(void){

    char read;
    int count;
    read = U2RXREG;
    putc(read);
    
    if(read=='U'){
        
        while(1)
        {
            LATE=(LATE & 0xFFE1)<<1;
            count++;
            count=15;
            if(count==15)
            {
                count=0;
            }

        }
    }
    if(read=='R')
    {
        while(1)
        {
            LATE=(LATE & 0xFFE1)<<1;
            count++;
            count=0;
            if(count==0)
            {
                count=15;
            }
            putstr("RESET");
        }
    }
    IFS1bits.U2RXIF = 0;

    
}


void putc(char byte2send)
{
    while(U2STAbits.UTXBF == 1); // Wait while UTXBF == 1
    U2TXREG = byte2send; // Copy byte2send to the UxTXREG register
}

void putstr(char *s){

	while(*s != '\0'){
		putc(*s);
		s++;
	}
	
}
