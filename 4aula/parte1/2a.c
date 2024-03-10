#include<detpic32.h>

void delay(int ms);

int main(void){
    //reset
    LATE=(LATE & 0xFFF0);
    //configure ports
    TRISE=(TRISE & 0xFFF0);

    int count=0;

    while(1){
        LATE=count;
        //wait 0.5s
        delay(500);
        //counter
        count = (count + 1) & 0x000F;
    }
return 0;
}
//Função delay
void delay(int ms){
    
    resetCoreTimer();
    while(readCoreTimer()<20000*ms);

}