/*******************************************************
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>

void main(){
    DDRC =0xff;
    PORTC = 0x00;
    while (1){
        PORTC.0 = 1;
        delay_ms(1000);
        PORTC.0= 0;
        delay_ms(1000);
        
        PORTC.1 = 1;
        delay_ms(1000);
        PORTC.1= 0;
        delay_ms(1000);

        PORTC.2 = 1;
        delay_ms(1000);
        PORTC.2= 0;
        delay_ms(1000);
        
        PORTC.3 = 1;
        delay_ms(1000);
        PORTC.3= 0;
        delay_ms(1000);
        
        PORTC.4 = 1;
        delay_ms(1000);
        PORTC.4= 0;
        delay_ms(1000);
        
        PORTC.5 = 1;
        delay_ms(1000);
        PORTC.5= 0;
        delay_ms(1000);
        
        PORTC.6 = 1;
        delay_ms(1000);
        PORTC.6= 0;
        delay_ms(1000);
        
        PORTC.7 = 1;
        delay_ms(1000);
        PORTC.7= 0;
        delay_ms(1000);        
    }
}
