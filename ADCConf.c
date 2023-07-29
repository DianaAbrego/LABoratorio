/* 
 * File:   ADCConf.c
 * Author: Diana Abrego
 *
 * Created on 18 de julio de 2023, 04:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
///
#include "ADCConf.h"
#define _XTAL_FREQ 4000000 //La frecencia que yo utlize para el delay

void adc_init( int channel){
 
    if (channel == 0){
        PORTAbits.RA0=0;        //EL BIT 0 DEL PUERTO A 
        TRISAbits.TRISA0=1;     // EL BIT 0 PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS0=1;       //USAR ANSEL 0 EN ra0 ANALOGO RA0
    }
    if (channel == 1){
        PORTAbits.RA1=0;        //EL BIT 1 DEL PUERTO A 
        TRISAbits.TRISA1=1;     // EL BIT 1 PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS1=1;       //USAR ANSEL 1 EN ra1 ANALOGO RA1
    }
    if (channel == 2){
        PORTAbits.RA2=0;        //EL BIT 2 DEL PUERTO A 
        TRISAbits.TRISA2=1;     // EL BIT 2 PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS2=1;       //USAR ANSEL  EN ra2 ANALOGO RA2
    }
    if (channel==3){
        PORTAbits.RA3=0;        //EL BIT 0 DEL PUERTO A 
        TRISAbits.TRISA3=1;     // EL BIT 0 PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS3=1;       //USAR ANSEL 0 EN ra0 ANALOGO RA0
    }
    if (channel==4){
        PORTAbits.RA5=0;        //EL BIT 0 DEL PUERTO A 
        TRISAbits.TRISA5=1;     // EL BIT 0 PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS4=1;       //USAR ANSEL 4 EN ra4 ANALOGO RA4
    }
    if (channel==5){
        PORTEbits.RE0=0;        //EL BIT 0 DEL PUERTO E
        TRISEbits.TRISE0=1;     // EL BIT E PUERTO ENTRADA  EL BIT 0
        ANSELbits.ANS5=1;       //USAR ANSEL 5 EN ra5 ANALOGO RA5
    }
    
    if (channel==6){
        PORTEbits.RE1=0;        //EL BIT 0 DEL PUERTO E
        TRISEbits.TRISE1=1;     // EL BIT 1 PUERTO ENTRADA  EL BIT 1
        ANSELbits.ANS6=1;       //USAR ANSEL  6 EN ra0 ANALOGO RE6
    }
    if (channel==7){   
        //PORTEbits.RE2=0;        //EL BIT 2 DEL PUERTO E
        TRISEbits.TRISE2=1;     // EL BIT 2 PUERTO ENTRADA  EL BIT 2
        ANSELbits.ANS7=1;       //USAR ANSEL 7 EN ra0 ANALOGO RE2
    }
    if (channel==8){
        PORTAbits.RA7=0;        //EL BIT 7 DEL PUERTO A
        TRISAbits.TRISA7=1;     // EL BIT 7 PUERTO ENTRADA  EL BIT 7
        ANSELbits.ANS7=1;       //USAR ANSEL 7 EN ra7 ANALOGO RA7
    }
    if (channel==9){
        PORTBbits.RB2=0;        //EL BIT 2 DEL PUERTO B 
        TRISBbits.TRISB2=1;     // EL BIT 2 PUERTO ENTRADA  EL BIT 2
        ANSELHbits.ANS8=1;       //USAR ANSEL 8 EN ra8 ANALOGO RB2
    }
    if (channel==10){
        PORTBbits.RB3=0;        //EL BIT 3 DEL PUERTO B
        TRISBbits.TRISB3=1;     // EL BIT 3 PUERTO ENTRADA  EL BIT 
        ANSELHbits.ANS9=1;       //USAR ANSEL 9 EN ra3 ANALOGO RB3
    
    }
    if (channel==11){
        PORTBbits.RB1=0;        //EL BIT 1 DEL PUERTO B
        TRISBbits.TRISB1=1;     // EL BIT 1 PUERTO ENTRADA  EL BIT 1
        ANSELHbits.ANS10=1;       //USAR ANSEL 10 EN rB1 ANALOGO RB1
    }
    
    if (channel==12){
        PORTBbits.RB4=0;        //EL BIT 4 DEL PUERTO B
        TRISBbits.TRISB4=1;     // EL BIT 4 PUERTO ENTRADA  EL BIT 4
        ANSELHbits.ANS11=1;       //USAR ANSEL 11 EN rb4 ANALOGO RB4
    }
    if (channel==13){
        PORTBbits.RB0=0;        //EL BIT 0 DEL PUERTO A 
        TRISBbits.TRISB0=1;     // EL BIT 0 PUERTO ENTRADA  EL BIT 0
        ANSELHbits.ANS12=1;       //USAR ANSEL 0 EN ra0 ANALOGO RB0
    }
    if (channel==14){
        PORTBbits.RB5=0;        //EL BIT 5 DEL PUERTO B
        TRISBbits.TRISB5=1;     // EL BIT 5 PUERTO ENTRADA  EL BIT 5
        ANSELHbits.ANS13=1;       //USAR ANSEL 13 EN ra0 ANALOGO RB5
    }
    ADCON0bits.ADCS1=0;
    ADCON0bits.ADCS0=1;     //fosc/8
    ADCON0bits.ADCS= 01;  
    ADCON1bits.VCFG1=0;     //VSS
    ADCON1bits.VCFG0=0;     //VDD 
    ADCON1bits.ADFM=0;      //JUSTIFICADO IZQUIERDA
    ADCON0bits.ADON=1;      //habilitar convertidor ADC
    
        __delay_us(100);
}
int adc_read (){
    ADCON0bits.GO = 1;         //Iniciar conversion
    while(ADCON0bits.GO == 1);  //No hacer nada mientras hace la conversion]
    ADIF = 0;                   //Apagar bandera del ADC
    int valADC;
    valADC = ADRESH;   //JUNTAR 10 BITS
    return  valADC;
    }

void adc_change_channel(int channel){
    if (channel ==1){
        ADCON0bits.CHS = 0b0000; //0
        __delay_ms(5);  
    }
     if (channel == 2){
        ADCON0bits.CHS = 0b0001; //1
        __delay_ms(5);  
    }
     if (channel ==3){
        ADCON0bits.CHS = 0b0010; //2
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b0011; //3
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b0100; //4
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b0101; //5
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b0110; //6
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b0111; //7
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1000; //8
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1001; //9
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1010; //10
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1011; //11
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1100; //12
        __delay_ms(5);  
    }
    if (channel){
        ADCON0bits.CHS = 0b1101; //13
        __delay_ms(5);  
    } 
}
int adc_get_channel(){
    return ADCON0bits.CHS;
}
