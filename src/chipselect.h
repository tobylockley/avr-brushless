#ifndef _CHIPSELECT_H_
#define _CHIPSELECT_H_

#include <avr/io.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
	#include "chipselect_m328p.h"
#elif defined (__AVR_ATmega8__)
	#include "chipselect_m8.h"
#else
	#error "Device not supported by avr-brushless."
#endif

//--!!!!!--MOVE THIS--!!!!!--//
#define RC_DDR			DDRD
#define RC_PORT			PORTD
#define RC_PIN			PIND
#define RC				2

#endif /* _CHIPSELECT_H_ */
