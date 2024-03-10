//contador crescente de módulo 10 atualizadoa a 1 frequencia de 4Hz
#include <detpic32.h>

int main(void)
{
    TRISB = TRISB & 0x80FF; // 1000 0000 1111 1111
    TRISD = TRISD & 0xFF9F; // 1111 1111 1001 1111
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    char ch;

    while(1)
    {
        ch = getChar();
        

        if(ch == 'a' || ch == 'A')
        {
            LATB = LATB & 0x80FF | 0x0100;
        }
        else if(ch == 'b' || ch == 'B')
        {
            LATB = LATB & 0x80FF | 0x0200;
        }
        else if(ch == 'c' || ch == 'C')
        {
            LATBbits.LATB10 = 1;
        }
        else if(ch == 'd' || ch == 'D')
        {
            LATBbits.LATB11 = 1;
        }
        else if(ch == 'e' || ch == 'E')
        {
            LATBbits.LATB12 = 1;
        }
        else if(ch == 'f' || ch == 'F')
        {
            LATBbits.LATB13 = 1;
        }
        else if(ch == 'g' || ch == 'G')
        {
            LATBbits.LATB14 = 1;
        }

    }
    return 0;
}

/*
#include <detpic32.h>

void delay(int ms);

int main(void){
    
    //reset
    LATD = (LATD & 0xFF9F);
    LATB = (LATB & 0x80FF);
    // Configure ports
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);

    //configure dysplay
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        char c = getChar();
        switch (c){
        case 'a':
        case 'A':
            LATB =   0x0100;   // RB8 = 1
            break;
        case 'b':
        case 'B':
            LATB =   0x0200;   // RB9 = 1
            break;
        case 'c':
        case 'C':
            LATB =   0x0400;   // RB10 = 1
            break;
        case 'd':
        case 'D':
            LATB =   0x0800;   // RB11 = 1
            break;
        case 'e':
        case 'E':
            LATB =   0x1000;   // RB12  = 1
            break;
        case 'f':
        case 'F':
            LATB =   0x2000;   // RB13 = 1
            break;
        case 'g':
        case 'G':
            LATB =   0x4000;   // RB14 = 1
            break;
        default:
            break;
        }
    
    }
    return 0;
}



*/