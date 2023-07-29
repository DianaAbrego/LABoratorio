/*
 * File:   USART.c
 * Author: abrdi
 *
 * Created on 28 de julio de 2023, 7:34
 */


#include <xc.h>
#include "USART.h"    
#define _XTAL_FREQ 1000000

void UART_RX_CONFIG(uint16_t baudrate){
    TXSTAbits.BRGH = 1;     //HIGH SPEED BAUD RATE      AMBOS
    BAUDCTLbits.BRG16 = 1;  //USAR 16 BITS PARA BAUDIOS AMBOS
    
    if(baudrate==9600){
        SPBRG = 103;        //PARA TENER UN BAUD RATE DE 9615, casi 9600  AMBOS
        SPBRGH = 0;         //                                            AMBOS
    }
    
    RCSTAbits.SPEN = 1;     //CONFIGURA TX Y RX como pines seriales   RX AMBOS
    RCSTAbits.RX9 = 0;      //Solo usaremos 8 bits, no 9             RX
    RCSTAbits.CREN = 1;     //En modo asincrono recibo continuamente   RX
    //CONFIG interrupciones
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1; //RECEPCION INTERRUPCION
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1; 
}

void UART_TX_CONFIG(uint16_t baudrate){
    //CONFIG TX, transmisor
    TXSTAbits.SYNC = 0;     //COMUNICACION ASINCRONA    TX
    TXSTAbits.BRGH = 1;     //HIGH SPEED BAUD RATE      AMBOS
    BAUDCTLbits.BRG16 = 1;  //USAR 16 BITS PARA BAUDIOS AMBOS
    
    if(baudrate==9600){
        SPBRG = 103;        //PARA TENER UN BAUD RATE DE 9615, casi 9600  AMBOS
        SPBRGH = 0;         //                                            AMBOS
    }
    
    TXSTAbits.TXEN = 1;     //habiliatr transmisor                      TX
    
    //CONFIG interrupciones
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1; //RECEPCION INTERRUPCION
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1; 
}
void UART_write_char (char c){ 
    while(PIR1bits.TXIF){
        TXREG = c; // registro guarda en valor del caracter
    }
}
char UART_read_char (){
    return TXREG;
 
}
