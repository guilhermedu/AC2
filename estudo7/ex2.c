#include <detpic32.h>

volatile unsigned char voltage =0; // Global variable 
char tobcd(unsigned char value);
void send2displays(unsigned char value);

void _int_(27) isr_adc(void)
{
    int i;
    int sum=0;
    int *p=(int *) &ADC1BUF0;
    for(i=0;i<8;i++)
    {
        sum+=p[i*4];
    }
    //calculate amplitude voltage 
    int v=((sum / 8)*33 +511 )/1023;

    voltage = tobcd(v);
    //Reset AD1If flag
    IFS1bits.AD1IF = 0;   
}

int main(void)
{
    unsigned int cnt =0;
    // configure all (digital i/o,analog input,A/D module , interrupts)
    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 7; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    // configure display
    TRISB=TRISB & 0x80FF;
    TRISD=TRISD & 0xFF9F;

    // Configure interrupt system
    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts to 2
    IEC1bits.AD1IE = 1; // enable A/D interrupts
    IFS1bits.AD1IF = 0; // clear A/D interrupt flag

    EnableInterrupts(); // Global Interrupt enable
    //
    while(1)
    {
        if(cnt== 0)  //0,200ms,400ms,...(5 samples/ second)
        {
            AD1CON1bits.ASAM=1;   // Start A/D conversion
        }

         // Send "voltage" value to displays
        send2displays(voltage);
        cnt=(cnt + 1) % 20;
        // wait 100ms
        resetCoreTimer();
        while(readCoreTimer()<20000);





    }
    return 0;
}

void send2displays(unsigned char value)
{  static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
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

char tobcd(unsigned char value)
{
    return ((value / 10)<<4 ) + (value % 10);
}