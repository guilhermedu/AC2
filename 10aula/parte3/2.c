#include <detpic32.h>

int main(void)
{
    //configureUART2(115200,N,8,1);
    //1-Configure BaudRate Generator
    U2BRG = ((20000000 + 8 * 19200) / (16 * 19200)) - 1;
    U2MODEbits.BRGH = 0; //divisao por 16
    //2-Configure number of data bits, parity and number of stop bits
    // (see U1MODE register)
    U2MODEbits.PDSEL = 0; //8 bits sem paridade
    U2MODEbits.STSEL = 1; //1 stop bit
    //3-Enable the transmitter and receiver modules (see register U1STA)
    U2STAbits.UTXEN = 1; //transmissao
    U2STAbits.URXEN = 1; //rececao
    //4-Enable UART2 (see register U1MODE)
    U2MODEbits.ON = 1; //ativar UART2
    //config RD11 as output
    TRISDbits.TRISD11 = 0;

    // config RD11 as output
    LATD = LATD & 0xF7FF;
    TRISD = TRISD & 0xF7FF;
    while(1)
    {
        //wait until buffer U2STAbits.TRMT == 1
        while(U2STAbits.TRMT == 0);
        //set RD11
        LATD = LATD | 0x0800; 
        //wait 1 second
        putstr("12345");
        //reset RD11
         LATD = LATD & 0xF7FF;
        //wait 1 second
        delay(1000);
    }
    return 0;
}

void putstr(char *str){
    while (*str != '\0'){
        putc(*str); 
        str++;
    }
}

void putc(char byte) {
    while(U2STAbits.UTXBF == 1);// wait while UART2 UTXBF == 1
    // Copy "byte" to the U2TXREG register
    U2TXREG = byte;
}

//Funcao delay
void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000 * ms);
}
