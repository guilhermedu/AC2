#include <detpic32.h>

void setPWM(unsigned int dutyCycle);


int main(void)
{
    //T3 a 100
    T3CONbits.TCKPS = 2;        
    PR3 = 49999;                         
    TMR3 = 0;                   
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;     //PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =1;   //Use timer T2 as the time base for PWM generation
    OC1RS = 12500;          //Ton constant
    OC1CONbits.ON = 1;      //Enable OC1 module

   

   

    while (1);

    return 0;
}

void setPWM(unsigned int dutyCycle)
{
    OC1RS = (dutyCycle*PR3)/100;
}