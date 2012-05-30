#ifndef POWERSTAGE_H
#define POWERSTAGE_H

#include <avr/interrupt.h>
#include "chipselect.h"

extern volatile uint8_t pwm_pin_select;
extern volatile uint8_t comm_state;

void powerstage_init(void);
void commutate_motor(void);
void set_pwm(uint8_t newval);

#define PWM_BOTTOM			155 //Range reduced to 255-155 = 100, but frequency increased to 20KHz
#define PWM_RANGE			(255 - PWM_BOTTOM)

//Are the outputs active low? Inspect circuit diagram to determine.
// 1 = TRUE, 0 = FALSE
#define LOWSIDE_ACTIVE_LOW 	0
#define HIGHSIDE_ACTIVE_LOW 0


//===================================//
//        ESC PIN DEFINITIONS        //
//===================================//
//Consult microcontroller data sheet before adjusting values
//	DDR  - Data Direction Register
//	PORT - I/O port name

//---------OUTPUTS----------//
#define LOWSIDE_PORT	PORTD

//Channel A
#define AH_DDR		DDRD
#define AH_PORT		PORTD
#define AH			7

#define AL_DDR		DDRD
#define AL_PORT		PORTD
#define AL			3

//Channel B
#define BH_DDR		DDRB
#define BH_PORT		PORTB
#define BH			2

#define BL_DDR		DDRD
#define BL_PORT		PORTD
#define BL			4

//Channel C
#define CH_DDR		DDRB
#define CH_PORT		PORTB
#define CH			0

#define CL_DDR		DDRD
#define CL_PORT		PORTD
#define CL			5
					

/************** MOSFET PIN STATES **************/

//Predefined macro functions for mosfet states based on whether logic is active high or low.
//Turn off corresponding high/low pin so it is not possible to create a short
//These do not need to be changed!!
//
//SET_X_LOW/HIGH()
//CLR_X_LOW/HIGH()
//GET_X_LOW()

#if (LOWSIDE_ACTIVE_LOW == 0)
	//Active HIGH
	
	//A test to determine whether the lowside mosfets are on/off
	#define GET_AL() ((AL_PORT & (1 << AL)) ? 1 : 0)
	#define GET_BL() ((BL_PORT & (1 << BL)) ? 1 : 0)
	#define GET_CL() ((CL_PORT & (1 << CL)) ? 1 : 0)
	
	#define AL_OFF() (AL_PORT &= ~(1 << AL))
	#define BL_OFF() (BL_PORT &= ~(1 << BL))
	#define CL_OFF() (CL_PORT &= ~(1 << CL))
#else
	//Active LOW
	
	//A test to determine whether the lowside mosfets are on/off
	#define GET_AL() ((AL_PORT & (1 << AL)) ? 0 : 1)
	#define GET_BL() ((BL_PORT & (1 << BL)) ? 0 : 1)
	#define GET_CL() ((CL_PORT & (1 << CL)) ? 0 : 1)
	
	#define AL_OFF() (AL_PORT |= (1 << AL))
	#define BL_OFF() (BL_PORT |= (1 << BL))
	#define CL_OFF() (CL_PORT |= (1 << CL))
#endif
	
#if (HIGHSIDE_ACTIVE_LOW == 0)
	//Active HIGH
	#define AH_OFF() (AH_PORT &= ~(1 << AH))
	#define BH_OFF() (BH_PORT &= ~(1 << BH))
	#define CH_OFF() (CH_PORT &= ~(1 << CH))
	
	#define AH_ON() (AL_OFF(), AH_PORT |= (1 << AH))
	#define BH_ON() (BL_OFF(), BH_PORT |= (1 << BH))
	#define CH_ON() (CL_OFF(), CH_PORT |= (1 << CH))
#else
	//Active LOW
	#define AH_OFF() (AH_PORT |= (1 << AH))
	#define BH_OFF() (BH_PORT |= (1 << BH))
	#define CH_OFF() (CH_PORT |= (1 << CH))
	
	#define AH_ON()	(AL_OFF(), AH_PORT &= ~(1 << AH))
	#define BH_ON() (BL_OFF(), BH_PORT &= ~(1 << BH))
	#define CH_ON() (CL_OFF(), CH_PORT &= ~(1 << CH))
#endif

#if (LOWSIDE_ACTIVE_LOW == 0)
	//Active HIGH
	#define AL_ON() (AH_OFF(), AL_PORT |= (1 << AL))
	#define BL_ON() (BH_OFF(), BL_PORT |= (1 << BL))
	#define CL_ON() (CH_OFF(), CL_PORT |= (1 << CL))
#else
	//Active LOW
	#define AL_ON() (AH_OFF(), AL_PORT &= ~(1 << AL))
	#define BL_ON() (BH_OFF(), BL_PORT &= ~(1 << BL))
	#define CL_ON() (CH_OFF(), CL_PORT &= ~(1 << CL))
#endif

#define POWER_OFF() ( AH_OFF(), \
					  BH_OFF(), \
					  CH_OFF(), \
					  AL_OFF(), \
					  BL_OFF(), \
					  CL_OFF()  )

#endif //#ifndef POWERSTAGE_H
