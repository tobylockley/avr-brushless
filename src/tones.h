#ifndef TONES_H
#define TONES_H

#include "chipselect.h"
#include "powerstage.h"

void tone(uint8_t loops, uint8_t wait);
void tone_low(void);
void tone_med(void);
void tone_high(void);

#endif //#ifndef TONES_H
