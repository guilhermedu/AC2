#include <detpic32.h>

int N = 4;
int V =0;
void send2displays(unsigned char value);
unsigned char tobcd(unsigned char value);


int main()
{
    TRISE=TRISE & 0xFF00;
    LATE=LATE & 0xFF00;

    LATD=LATD & 0xFF9F;
    LATB=LATB & 0x80FF;

    TRISD=TRISD & 0xFF9F;
    TRISB=TRISB & 0x80FF;

    // configuração do ADC
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

    // configuração do timer2
    T2CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = (5000000/100)-1; // Fout = 20MHz / (4 * ( + 1)) = 100 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts();

    while(1)
    {
        AD1CON1bits.ASAM=1;
        while(IFS1bits.AD1IF==0);
        int *p= (int *)(&ADC1BUF0);
        int i;
        int average;
        for(i=0;i<N;i++)
        {
            average += p[i * 4];
        }
        average=average/N;
        V=((average * 11 + 511 )/1023)+1; 
        //não se é preciso if mas acho que não;
        switch (V)
        {
        case 1:
            LATE=(LATE & 0xFF00) | 0x0001;
            break;
        case 2:
            LATE=(LATE & 0xFF00) | 0x0003;
            break;
        case 3:
            LATE =(LATE & 0xFF00) | 0x0007;
            break;
        case 4:
            LATE=(LATE & 0xFF00) | 0x000F;
            break;
        case 5:
            LATE=(LATE & 0xFF00) | 0x001F;
            break;
        case 6:
            LATE=(LATE & 0xFF00) | 0x003F;
            break;
        case 7:
            LATE=(LATE & 0xFF00) | 0x0007F;
            break;
        case 8:
            LATE=(LATE & 0xFF00) | 0x000FF;
            break;
        default:
            break;
        }
        printInt(V,10 | 2 << 16);
        putChar('\r');

    }
}

    void _int_(8) isr_T2(void)
    {
        send2displays(tobcd(V));
        IFS0bits.T2IF = 0; // Reset T2IF flag
       
    }










void send2displays(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
                                    //   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F   
    static char displayFlag = 0; // static variable: doesn't loose its
                                // value between calls to function
    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(!displayFlag){
        LATD = (LATD & 0xFF9F) | 0x0020;
        digit_low = display7Scodes[digit_low];
        LATB = (LATB & 0x80FF ) | digit_low << 8;
    }
    // else send digit_high to didplay_high
    else{
        LATD = (LATD & 0xFF9F) | 0x0040;
        digit_high = display7Scodes[digit_high];
        LATB = (LATB & 0x80FF ) | digit_high << 8;
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}









unsigned char tobcd(unsigned char value)
{
    return (((value/10)<<4) + (value%10));
}