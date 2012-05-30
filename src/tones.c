#include "tones.h"

void tone(uint8_t wait, uint8_t loops)
{
	uint8_t i;
    TIMER0_ON_P64();
    POWER_OFF();
    set_pwm(4);
	for (i=0; i<loops; i++) {
		pwm_pin_select = BL;
		AH_ON();
		TCNT0 = 0;
		while (TCNT0 < wait);
		TCNT0 = 0;
		while (TCNT0 < wait);
		AH_OFF();
		
		pwm_pin_select = AL;
		BH_ON();
		TCNT0 = 0;
		while (TCNT0 < wait);
		TCNT0 = 0;
		while (TCNT0 < wait);	
		BH_OFF();
	}
	set_pwm(0);
	POWER_OFF();
	TIMER0_OFF();
}

void tone_low(void)
{
	tone(239, 39);
}

void tone_med(void)
{
	tone(190, 49);
}

void tone_high(void)
{
	tone(159, 59);
}
