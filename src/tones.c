#include "chipselect.h"
#include "powerstage.h"
#include "tones.h"

void tone(uint8_t wait, uint8_t loops)
{
    uint8_t i;
    TIMER0_ON_P64();
    POWER_OFF();
    set_pwm(0.05*PWM_RANGE);
    for (i=0; i<loops; i++) {
        pwm_pinselect(BL);
        AH_ON();
        TCNT0 = 0;
        while (TCNT0 < wait);
        TCNT0 = 0;
        while (TCNT0 < wait);
        AH_OFF();

        pwm_pinselect(AL);
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

void tone_wait(uint8_t wait, uint8_t loops)
{
    uint8_t i;
    TIMER0_ON_P64();
    for (i=0; i<loops; i++) {
        TCNT0 = 0;
        while (TCNT0 < wait);
        TCNT0 = 0;
        while (TCNT0 < wait);
        TCNT0 = 0;
        while (TCNT0 < wait);
        TCNT0 = 0;
        while (TCNT0 < wait);
        BH_OFF();
    }
    TIMER0_OFF();
}

void tone_low(void)
{
    tone_F4();
}

void tone_med(void)
{
    tone_A4();
}

void tone_high(void)
{
    tone_C5();
}

void tone_C4(void)
{
    tone(223, 65);
}

void tone_E4(void)
{
    tone(175, 82);
}

void tone_F4(void)
{
    tone(164, 43);
    tone_wait(164, 44);
}

void tone_G4(void)
{
    tone(144, 98);
}

void tone_A4(void)
{
    tone(128, 55);
    tone_wait(128, 55);
}

void tone_C5(void)
{
    tone(105, 65);
    tone_wait(105, 66);
}

void tone_A5(void)
{
    tone(71, 132);
}

void tone_Cs6(void)
{
    tone(56, 166);
}

void tone_E6(void)
{
    tone(47, 198);
}
