/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 3/4/2023
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>
 unsigned char i,j,k;
 unsigned char segment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
void main(void)
{
    DDRB = 0XFF;
    DDRD = 0XFF;
    PORTB = 0xFF;
    PORTD = 0x00;

    while (1){
        for(i =0 ; i<10 ; i++){
            for(j =0 ;j<10 ; j++){
                for(k = 0 ; k<2 ; k++){
                    PORTD = segment[j];
                    PORTB.0 = 0;
                    delay_ms(200);
                    PORTB.0 = 1;
             
                    PORTD = segment[i];
                    PORTB.1 = 0;
                    delay_ms(200);
                    PORTB.1 = 1;      
                }
            }
        }
    }
}
