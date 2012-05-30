#include <avr/io.h>

void init_timers(void);


/************* REGISTERS *************/

//TIMSK
#define INIT_TIMSK	( (0 << TOIE0)  \
					| (0 << TICIE1) \
					| (0 << OCIE1A) \
					| (0 << OCIE1B) \
					| (0 << TOIE1)  \
					| (0 << OCIE2)  \
					| (0 << TOIE2)  )

//TIMER0
#define INIT_TCCR0	( (0 << CS02) \
					| (0 << CS01) \
					| (0 << CS00) )

		 
//TIMER1

#define INIT_TCCR1A	( (0 << COM1A1) \
					| (0 << COM1A0) \
					| (0 << COM1B1) \
					| (0 << COM1B0) \
					| (0 << FOC1A)  \
					| (0 << FOC1B)  \
					| (0 << WGM11)  \
					| (0 << WGM10)  )
		 
#define INIT_TCCR1B	( (0 << ICNC1) \
					| (0 << ICES1) \
					| (0 << WGM13) \
					| (0 << WGM12) \
					| (0 << CS12)  \
					| (0 << CS11)  \
					| (0 << CS10)  )

#define INIT_OCR1A	0
#define INIT_OCR1B	0

//TIMER2

#define INIT_TCCR2	( (0 << FOC2)  \
		 			| (0 << WGM20) \
		 			| (0 << COM21) \
		 			| (0 << COM20) \
		 			| (0 << WGM21) \
		 			| (0 << CS22)  \
		 			| (0 << CS21)  \
		 			| (0 << CS20)  )

#define INIT_OCR2	0
