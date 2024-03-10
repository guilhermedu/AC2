#include <detpic32.h>

#define NSamples 2

void delay(int ms)
{ 
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}
void send2displays(unsigned char value)
{
    static const char display7Scodes[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag=0;

    int low_d= value & 0x0F;
    

   
    
    LATB=(LATB & 0x80FF) | display7Scodes[low_d]<<8;
    LATDbits.LATD5=1;
    LATDbits.LATD6=0;
  

}

int main(void)
{
TRISBbits.TRISB4 = 1; // RBx digital output disconnected
AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
// mode an internal counter ends sampling and
// starts conversion
AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
// interrupt is generated. At the same time,
// hardware clears the ASAM bit
AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
AD1CON2bits.SMPI = NSamples-1; // Interrupt is generated after N samples
// (replace N by the desired number of
// consecutive samples)
AD1CHSbits.CH0SA = 4; // replace x by the desired input
// analog channel (0 to 15)
AD1CON1bits.ON = 1; // Enable A/D converter
// This must the last command of the A/D
// configuration sequence
// configurar portos como saída
TRISB=TRISB & 0x80FF;
TRISD=TRISD & 0xFF9F;
// configurar porto de saída RE1 
TRISEbits.TRISE1=0;
LATEbits.LATE1=0;

while(1)
{
    AD1CON1bits.ASAM = 1; // Start conversion

    while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done

    //PARTE i)
    int media=0;
    int i=0;
    int *p=(int *)(&ADC1BUF0);
    for(;i<NSamples;i++)
    {
        media+=p[i*4];
    }
    media=media / NSamples;

    printInt(media,16 | 3 << 16);
    putChar('\n');

    // parte ii)
    LATDbits.LATD5=1;
    LATDbits.LATD6=0;
    int value = (media * 9) / 1023;
    send2displays(value);

    //parte iii)
    LATEbits.LATE1= ! LATEbits.LATE1;

    IFS1bits.AD1IF == 0 ;
    delay(200);


}

return 0;
}
