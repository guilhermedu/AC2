#include <detpic32.h>

int N=4;
int V=0;

void delay(int ms);
void send2displays(unsigned char value);
unsigned char tobcd(unsigned char value);


int main(void)
{

    LATD=LATD & 0xFF9F;
    LATB=LATB & 0x80FF;
    //configuração de portos
    TRISE=TRISE & 0xFF00;
    TRISD=TRISD & 0xFF9F;
    TRISB=TRISB & 0x80FF;

 


    //configuração do ADC
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

    //configurar T2 e interrupções
    T2CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = (5000000/100)-1; // Fout = 20MHz / (32 * (62499 + 1)) = 100Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    EnableInterrupts();

    while(1)
    
}

void _int_(27) isr_ADC(void)
{
    int *p=(int *)(&ADC1BUF0);
    int i;
    int average=0;
    for(i=0;i<N;i++)
    {
        average+=p[i*4];
    }
    average=average/N;
    V=(average*15+511)/1023+1;

  

        switch (V)
        {
        case 1 :
            LATE=(LATE & 0xFF00) | 0x0001;
            break;
        case 2:
            LATE=(LATE & 0xFF00) | 0x0003;
            break;
        case 3:
            LATE=(LATE & 0xFF00) | 0x0007;
            break;
        case 4:
            LATE=(LATE & 0xFF00) | 0x000F;
            break;
        case 5:
            LATE=(LATE & 0xFF00) | 0x001F;
            break;
        case 6:
            LATE=(LATE & 0xFF00) | 0x0003F;
            break;
        case 7:
            LATE=(LATE & 0xFF00) | 0x007F;
            break;
        case 8:
            LATE=(LATE & 0xFF00) | 0x00FF;
            break;
        default:
            break;
        }

    delay(100);

    IFS1bits.AD1IF == 0;

}

void _int_(8) _isr_T2(void)
{
    send2displays(tobcd(V));
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag
}



void delay(int ms)
{
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);
}


void send2displays(unsigned char value)
{
    static const char send2Scodes[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    static char displayFlag=0;

    unsigned char dl=value & 0x0F;
    unsigned char dh=value >> 4;

    if(!displayFlag){
        LATD=(LATD & 0xFF9F) | 0x0020;
        dl=send2Scodes[dl];
        LATB=(LATB & 0x80FF) | dl << 8;
    }
    else{
        LATD=(LATD & 0xFF9F) | 0x0040;
        dh=send2Scodes[dh];
        LATB=(LATB & 0x80FF) | dh << 8;
    }
    displayFlag=!displayFlag;
}


unsigned char tobcd(unsigned char value)
{
    return (((value/10)<<4)+(value%10));
}
