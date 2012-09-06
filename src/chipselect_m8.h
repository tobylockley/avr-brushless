#ifndef _CHIPSELECT_M8_H_
#define _CHIPSELECT_M8_H_

//TODO

/************** PWM **************/
/*#define PWM_INIT()            ( TIMSK2 = (1 << OCIE2A) | (1 << TOIE2), \
                              TCCR2A = (1 << WGM21)  | (1 << WGM20)  ) //Enable interrupts, Fast PWM mode
#define PWM_COMP_vect       TIMER2_COMPA_vect //output compare interrupt vector
#define PWM_OVF_vect        TIMER2_OVF_vect    //overflow interrupt vector
#define PWM_COMP_REG        OCR2A
#define PWM_COUNT_REG       TCNT2
#define PWM_PRESCL          (1 << CS21) //clk/8
#define PWM_ON()            ( TCCR2B |= PWM_PRESCL )
#define PWM_OFF()           ( TCCR2B &= ~PWM_PRESCL )*/


/************** TIMER0 **************/
/*#define TIMER0_OFF()      ( TCCR0B &= ((1 << CS02) | (1 << CS01) | (1 << CS00)) )
#define TIMER0_ON_P64()     ( TIMER0_OFF(), TCCR0B |= (1 << CS01) | (1 << CS00) )*/

#endif  /* _CHIPSELECT_M8_H_ */
