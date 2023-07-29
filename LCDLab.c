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
#include <stdint.h>
#include "ADCConf.h"
#include "LCD8.h"
#include "USART.H"
#include <stdlib.h>
#include <string.h>

#define _XTAL_FREQ 1000000
#define RS RE0
#define EN RE1
//***************PROTOTIPO DE FUNCIONES**************

void setup(void);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
//Variables globales
char buffer[sizeof(unsigned int)*8+1];  //conversor de numero a cadena de caracter siu
unsigned int cpu =0;
//************** VARIABLES ***************************


//*********************interrupcion/

//****************MAIN********************************

 void main (void){
    setup();
    while(1){
        unsigned int ValADC, Vol ;
        
        ValADC = adc_read();
        
        //UART_write_char("\r49");
        UART_write_char("\r_ \n 1) .Lectura Pot \n");
        UART_write_char("\r_ 2) + ___ - para sumar contador \n");
        
        while(PIR1bits.RCIF==0);    //hasta que haya interrupcion continua
        
        if(UART_read_char()==0b00110001){ //1
            UART_write_char("\r_ Numero actual POT_ \n");
            UART_write_char(utoa(buffer,ValADC,10));  //convertir variable a cadena y mostrarlo
            UART_write_char("\r");
        }
        
        if(UART_read_char()==0b00110010){ //2
            UART_write_char("\r Escriba + o - para modificar el contador \n");
            while(PIR1bits.RCIF==0);        //no hace nada al escribir
            if(UART_read_char()== 0b00101011){ //+
                cpu++;
            }
            if(UART_read_char()==0b00101101){ //-
                cpu--;
            }
            UART_write_char("\r Total:");
            UART_write_char(utoa(buffer,cpu,10));  //convertir variable a cadena y mostrarlo
            UART_write_char ("\r");                    //enter
            PIR1bits.RCIF = 0;             //apagar interrupcion
            //while(PIR1bits.RCIF==0);    //hasta que haya interrupcion continua
        }
        
        
        Vol = map(ValADC,0,255,0,500);
        char DECVOL[3]; //arreglo para convertir el voltaje 
        DECVOL[0]=Vol/100+48;
        DECVOL[1]=(Vol/10)%10+48;
        DECVOL[2]= Vol%10+48;
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Pot1:");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(DECVOL[0]);
        Lcd_Write_Char('.');
        Lcd_Write_Char(DECVOL[1]);
        Lcd_Write_Char(DECVOL[2]);
        Lcd_Write_Char('V');
        
        
        char contador[3];
        contador[0]=cpu/100+48;
        contador[1]=(cpu/10)%10+48;
        contador[2]=cpu%10+48;
        Lcd_Set_Cursor(1,8);
        Lcd_Write_String("Contador:");
        Lcd_Set_Cursor(2,8);
        Lcd_Write_Char(contador[0]);
        //Lcd_Write_Char('.');
        Lcd_Write_Char(contador[1]);
        Lcd_Write_Char(contador[2]);
        Lcd_Write_Char('V');
  
        __delay_ms(500);
    }
    return;
}

void setup(void)
{ 
    ANSEL = 0;
    ANSELH = 0;
    TRISD = 0;
    TRISE = 0;
    PORTB = 0;
    TRISB =0;
    adc_init(0);
    Lcd_Init();
    OSCCONbits.IRCF = 0b110; //1Mh
    OSCCONbits.SCS = 1;
    UART_TX_config (9600);
    UART_RX_config (9600);
 

}
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh){
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


