/*
 * File:   llift2.c
 * Author: bawan
 *
 * Created on 31 July, 2024, 7:17 PM
 */


#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF  
#include <xc.h>

void delay(unsigned int a)
{
   while(a--) ;
}
void enable()
{
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
}
void lcd(char cmd,char data )
{
    RE0=cmd;
    PORTD=data;
    enable();
}
void string(char cmd,char data[])
{
    RE0=cmd;
    for(int i=0;data[i]!='\0';i++)
    {
    PORTD=data[i];
    enable();
    }
}
void main(void) 
{
    int floor,sensor;
     
    PORTA=0x00;
    PORTB=0X00;
    PORTC=0X00;
    PORTD=0X00;
    PORTE=0X00;
    TRISA=0X0F; 
    TRISB=0X0F;
    TRISC=0X00;
    TRISD=0X00;
    TRISE=0X00;
    ANSEL=0x00;
    ANSELH=0X00;
    lcd(0,0x38);
    lcd(0,0x0E);
    
    while(1) 
    {
        if(RA0==1)
        {
            floor=0;
        }
        if(RA1==1)
        {
            floor=1;
        }
        if(RA2==1)
        {
            floor=2;
        }
        if(RA3==1)
        {
            floor=3;
        }
        if(RB0==0)
        {
            sensor=0;
              lcd(0,0x80);
            string(1,"ground floor");
        }
        if(RB1==0)
        {
            sensor=1;
              lcd(0,0x80);
             string(1,"first floor");
        }
        if(RB2==0)
        {
            sensor=2;
              lcd(0,0x80);
             string(1,"second  floor");
        }
        if(RB3==0)
        {
            sensor=3;
              lcd(0,0x80);
             string(1,"third floor");
        }
        if(floor>sensor)
        {
            RC1=0;RC0=1;
        }
        if(floor<sensor)
        {
            RC1=1;RC0=0;
        }
        if(floor==floatswitch)
        {
            RC0=RC1=0;
        }
        
    }
    
    
}
