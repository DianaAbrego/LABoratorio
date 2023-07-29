/*
 * * File:  SETUP BOTONES 
 * Author: DIANA ABREGO 
 * Comments:
 * Revision history: 
 
 */
 

  
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
///FUNCION PARA CONF PULLUP BOTONES//
void UART_RX_config (uint16_t baudrate);
void UART_TX_config (uint16_t baudrate);
void UART_write_char (char *c);
char UART_read_char ();

#endif	/* USART_H */
