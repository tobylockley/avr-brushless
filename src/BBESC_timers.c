#include "BBESC_timers.h"

inline void init_timers(void)
{
	//see BBESC_timers.h for register settings
	TIMSK = INIT_TIMSK;
	TCCR0 = INIT_TCCR0;
	TCCR1A = INIT_TCCR1A;
	TCCR1B = INIT_TCCR1B;
	OCR1A = INIT_OCR1A;
	OCR1B = INIT_OCR1B;
	TCCR2 = INIT_TCCR2;
	OCR2 = INIT_OCR2;
}
