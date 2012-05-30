
#ifndef CHIPSELECT_H
#define CHIPSELECT_H

#include <avr/io.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#include "chipselect_m328p.h"
#elif defined (__AVR_ATmega8__)
#include "chipselect_m8.h"
#else
#error "Device not supported by avr-brushless."
#endif

//----------INPUTS----------//
//RC servo signal
#define RC_DDR			DDRD
#define RC_PORT			PORTD
#define RC_PIN			PIND
#define RC				2

#endif //#ifndef CHIPSELECT_H
