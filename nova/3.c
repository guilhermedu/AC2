#include <detpic32.h>

volatile int counter = 0;

int main(void){ 
    
    TRISE = TRISE & 0xFFE1;

   
    U2BRG = ((PBCLK + 8 * 9600) / (16 * 9600)) - 1;

    U2MODEbits.BRGH =0;
    U2MODEbits.PDSEL = 0b10;
    U2MODEbits.STSEL = 1;
    

    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 1;

    EnableInterrupts();

    while(1);

    return 0;
}
void _int_(32) isr_uart2(void){
    char c;
    c = getc();
    if (c == 'U'){
       LATE = (LATE & 0xFFE1) | counter;
       counter++;
    
    } else if ((c == 'R') || (counter == 15)) {
        putstr("RESET");
        putc('\n');
        counter = 0;
    }
    
    IFS1bits.U2RXIF = 0;
}





void putc(char byte) {
    while (U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

char getc(void) {
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

void putstr(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++){
        putc(str[i]);
    }
}


