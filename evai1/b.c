#include <detpic32.h>

int N=2;
int V=0;
void send2displays(unsigned char value);
unsigned char tobcd(unsigned char value);
void delay(int ms);

int main(void)
{
    //configurar portos
    TRISD=TRISD & 0xFF9F;
    TRISB=TRISB & 0x80FF;

    //configurar adc
    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = N-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence

    //configurar T2 e a sua interrupção
    T2CONbits.TCKPS = 2; // 1:4 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = (5000000/120)-1; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts();

    while(1)
    {
        AD1CON1bits.ASAM = 1; // Start conversion
        while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
        int *p=(int *)(&ADC1BUF0);
        int i;
        int average=0;
        for(i=0;i<N;i++)
        {
            average+=p[i*4];
        }
        average=average/N;
        V=((average*45 +511)/1023)+20;

        delay(10);
    }

}

void _int_(8) _isr_T2(void)
{
    send2displays(tobcd(V));
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag
}

void send2displays(unsigned char value)
{
    static const char send2Scodes[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag=0;

    unsigned char dl=value & 0x0F;
    unsigned char dh=value>>4;

    if(!displayFlag)
    {
        LATD=(LATD & 0xFF9F) | 0x0020;
        dl=send2Scodes[dl];
        LATB=(LATB & 0x80FF) | dl<<8;
    }
    else{
        LATD=(LATD & 0xFF9F) | 0x0040;
        dh=send2Scodes[dh];
        LATB=(LATB & 0x80FF) | dh<<8;
    }
    displayFlag=!displayFlag;
}

void delay(int ms){
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}









unsigned char tobcd(unsigned char value)
{
    return (((value/10)<<4)+(value%10));
}
