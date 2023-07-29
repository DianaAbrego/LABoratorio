/*
 * File:   PRELCD.c
 * Author: abrdi
 *
 * Created on 24 de julio de 2023, 8:20
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//***************LIBRERIAS***************************
#include <xc.h>
#include "ADCConf.H"
#define _XTAL_FREQ 8000000 //La frecencia que yo utlize para el delay
#include "LCD.H"
#include <stdio.h>
//***************PROTOTIPO DE FUNCIONES**************
float map(float value, float fromLow, float fromHigh,float toLow, float toHigh);
void setup(void);
//************** VARIABLES ***************************
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RB5
#define D6 RD6
#define D7 RD7

uint16_t ValAdc ; //
uint16_t valortemp;
uint16_t ValVol;

//char datos[20];
//****************MAIN********************************
void main(void) {
  setup();
  while(1)
  {
    ValAdc = adc_read();
    valortemp = map(ValAdc, 0, 255, 0, 500); //valor del voltaje en decimal   
    char Volt [3];
    Volt[0] = valortemp/100+48;
    Volt[1] = (valortemp/10)%10+48;
    Volt[2] = valortemp%10+48;
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Val Pot1");
    //Lcd_Write_String("Val Pot1");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char(Volt[0]);
    Lcd_Write_Char('.');
    Lcd_Write_Char(Volt[1]);
    Lcd_Write_Char(Volt[2]);
    // Lcd_Write_Char('V');
    __delay_ms(500);  
  } 
    return;
}

void setup(void)
{ 
    //CONFIGURACION PINES DIGITALES
    ANSEL = 0;
    ANSELH = 0;
    //CONFIGURACION I/O
    TRISB = 7;
    TRISA = 0B00000010;
    TRISC = 0; //SALIDA
    TRISD = 0; //SALIDA
    TRISE = 0; //SALIDA
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;  //MANDALE VOLTAJE 
    PORTD = 0;  //MANDARLE VOLTAJE 
    PORTE = 0; 
    
    //RE2 = 1;
    adc_init(0); //potenciomentro
    Lcd_Init();
    
    

}
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
 return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}