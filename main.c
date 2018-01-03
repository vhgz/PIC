#define _XTAL_FREQ 8000000

#include <xc.h>
#include "lcd.h"
#include <pic16f877a.h>
#include <stdio.h>
#include "Config_bits.h"
#include "ADC.h"

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