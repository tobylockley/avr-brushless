#include <avr/interrupt.h>
#include <util/atomic.h>

#include "chipselect.h"
#include "powerstage.h"

#define PWM_BOTTOM  (255 - PWM_RANGE)

volatile uint8_t pwm_pin_mask;
volatile uint8_t comm_state;

ISR(PWM_COMP_vect, ISR_NAKED)
{
    AL_OFF();
    BL_OFF();
    CL_OFF();
    reti();
}

ISR(PWM_OVF_vect)
{
    //LOWSIDE_PORT |= pwm_pin_mask;
    switch (pwm_pin_mask) {
    case (1 << AL):
        AL_ON();
        break;
    case (1 << BL):
        BL_ON();
        break;
    case (1 << CL):
        CL_ON();
        break;
    }
    /*switch (pwm_pin_select) {
    case AL:
        AL_ON();
        break;
    case BL:
        BL_ON();
        break;
    case CL:
        CL_ON();
        break;
    }*/
    if (PWM_BOTTOM > 0) PWM_COUNT_REG = PWM_BOTTOM;
}

void powerstage_init(void)
{
    //Set the mosfet pins to output
    AL_DDR |= (1 << AL);
    BL_DDR |= (1 << BL);
    CL_DDR |= (1 << CL);

    AH_DDR |= (1 << AH);
    BH_DDR |= (1 << BH);
    CH_DDR |= (1 << CH);

    //Turn all mosfets off
    POWER_OFF();

    //Set up PWM timer registers
    PWM_INIT();

    comm_state = 0;
}

void set_pwm(uint8_t newval)
{
    if (newval == 0) {
        PWM_OFF();
        PWM_COMP_REG = 0;
    }
    else {
        if (newval > PWM_RANGE) newval = PWM_RANGE; //clip value to permitted range
        if (PWM_COMP_REG == 0) PWM_ON();
        PWM_COMP_REG = PWM_BOTTOM + newval;
    }
}

void pwm_AL(void)
{
    pwm_pin_mask = (1 << AL);
}

void pwm_BL(void)
{
    pwm_pin_mask = (1 << BL);
}

void pwm_CL(void)
{
    pwm_pin_mask = (1 << CL);
}

void pwm_pinselect(uint8_t pin)
{
    //Public funtion to change PWM current pin
    //Must be on the LOWSIDE_PORT declared in the header
    //if (pin == AL || pin == BL || pin == CL) {
        pwm_pin_mask = (1 << pin);
    //}
}

void startDC(void)
{
    pwm_BL();
    AH_ON();
}

void commutate_motor(void)
{
    //When switching low side, extra logic tests are used to make sure if PWM was in an 'on' state,
    //  it will remain that way and visa versa

    //To make code more efficient, it is assumed that comm_state always starts at 0 after a MCU reset,
    //  and direction of rotation can not change during operation.

    //TODO: ADD IF STATEMENT FOR DIRECTION OF SPIN

    //Initialise zero crossing detection variables before commutation
    /*TCNT1 = 0;
    startZcLowTime = 0;
    newZCTime = 0;
    zcDetected = 0;
    if (comm_state % 2 == 0) {
        //Even number, Floating voltage going low -> high (rising)
        detectRisingBEMF();
    }
    else {
        //Odd number, Floating voltage going high -> low (falling)
        detectFallingBEMF();
    }*/

    comm_state %= 6; //causes comm_state to wrap to 0 when it reaches 6
    comm_state++;

    switch (comm_state) {
    case 1:
        //Do comparator stuff here before switching occurs
        //ADMUX = ADC_C;

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            if (GET_CL()) {
                CL_OFF();
                BL_ON(); //if mosfet from prev state was on, set next mosfet to on
                pwm_BL(); //Set pwm to lowside B
            }
            else {
                pwm_BL(); //Set pwm to lowside B
            }
        }
        //If mosfet was off, then the new phase will be activated on the next pwm interrupt,
        //  no need to do anything extra
        break;
    case 2:
        //ADMUX = ADC_A;

        AH_OFF();
        CH_ON();
        break;
    case 3:
        //ADMUX = ADC_B;

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            if (GET_BL()) {
                BL_OFF();
                AL_ON(); //if mosfet from prev state was on, set next mosfet to on
                pwm_AL(); //Set pwm to lowside A
            }
            else {
                pwm_AL(); //Set pwm to lowside A
            }
        }
        //If mosfet was off, then the new phase will be activated on the next pwm interrupt,
        //  no need to do anything extra
        break;
    case 4:
        //ADMUX = ADC_C;

        CH_OFF();
        BH_ON();
        break;
    case 5:
        //ADMUX = ADC_A;

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            if (GET_AL()) {
                AL_OFF();
                CL_ON(); //if mosfet from prev state was on, set next mosfet to on
                pwm_CL(); //Set pwm lowside C
            }
            else {
                pwm_CL(); //Set pwm lowside C
            }
        }
        //If mosfet was off, then the new phase will be activated on the next pwm interrupt,
        //  no need to do anything extra
        break;
    case 6:
        //ADMUX = ADC_B;

        BH_OFF();
        AH_ON();
        break;
    }
}
