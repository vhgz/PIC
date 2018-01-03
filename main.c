#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include "lcd.h"
#include <pic16f877a.h>
#include <stdio.h>

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

void ADC_Init()
{
   ADCON0 = 0x81;
   ADCON1 = 0x80;
}

unsigned int ADC_Read(unsigned char channel)
{
   if(channel > 7)
     return 0;

   ADCON0 &= 0xC5;
   ADCON0 |= channel<<3;
   __delay_ms(2);
   GO_nDONE = 1;
   while(GO_nDONE);
   return ((ADRESH<<8)+ADRESL);
}

int main()
{
  unsigned int a;
  unsigned int leitura;
  float AD_convertido;
  char ad_tratado_lcd[16];
  
   TRISA = 0xFF;
   TRISB = 0x00;
   TRISC = 0x00;
   TRISD = 0x00;
  ADC_Init();
  Lcd_Init();
 
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("LCD e ADC");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("MPLAB XC8");
    __delay_ms(2000);


    for(a=0;a<15;a++)
    {
        __delay_ms(300);
        Lcd_Shift_Left();
    }

    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Leitura ADC");
    
    
  while(1)
  {

 
  
     leitura = ADC_Read(0);
     PORTB = leitura;
     __delay_ms(100);
     AD_convertido = leitura * 0.00488;
     
    
    //sprintf(Buffer, "%.3g",b);
    Lcd_Set_Cursor(2,1);
    sprintf(ad_tratado_lcd,"%.3f V",AD_convertido);
    Lcd_Write_String(ad_tratado_lcd);
    __delay_ms(500);
     
     
  }
  return 0;
}