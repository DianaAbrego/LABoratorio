/*
 * * File:  SETUP BOTONES 
 * Author: DIANA ABREGO 
 * Comments:
 * Revision history: 
 
 */
 

  
#ifndef ADCCONF_H
#define	ADCCONF_H

#include <xc.h> // include processor files - each processor file is guarded.  
///FUNCION PARA CONF PULLUP BOTONES//
void adc_init(int channel);
int adc_read ();
void adc_change_channel(int channel);
int adc_get_channel();



#endif	/* ADCCONF_H */
