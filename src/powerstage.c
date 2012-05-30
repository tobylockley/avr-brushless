#include "powerstage.h"

volatile uint8_t pwm_pin_select;
volatile uint8_t comm_state;

ISR(PWM_COMP_vect)
{
	AL_OFF();
	BL_OFF();
	CL_OFF();
}

ISR(PWM_OVF_vect)
{
	LOWSIDE_PORT |= (1 << pwm_pin_select);
	PWM_COUNT_REG = PWM_BOTTOM;
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

void commutate_motor(void)
{
	//When switching low side, extra logic tests are used to make sure if PWM was in an 'on' state,
	//	it will remain that way and visa versa
	
	//To make code more efficient, it is assumed that comm_state always starts at 0 after a MCU reset,
	//	and direction of rotation can not change during operation.
	
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
				
		/*if (GET_CL()) {
			CL_OFF();
			BL_ON(); //if mosfet from prev state was on, set next mosfet to on
		}*/
		//If mosfet was off, then the new phase will be activated on the next pwm interrupt,
		//	no need to do anything extra
		pwm_pin_select = BL; //Set pwm to lowside B
		break;
	case 2:
		//ADMUX = ADC_A;
		
		AH_OFF();
		CH_ON();
	  	break;
	case 3:
		//ADMUX = ADC_B;
		
		/*if (GET_BL()) {
			BL_OFF();
			AL_ON(); //if mosfet from prev state was on, set next mosfet to on
		}*/
		//If mosfet was off, then the new phase will be activated on the next pwm interrupt,
		//	no need to do anything extra
		pwm_pin_select = AL; //Set pwm to lowside A
	  	break;
	case 4:
		//ADMUX = ADC_C;
		
		CH_OFF();
		BH_ON();
	  	break;
	case 5:
		//ADMUX = ADC_A;
		
		/*if (GET_AL()) {
			AL_OFF();
			CL_ON(); //if mosfet from prev state was on, set next mosfet to on
		}*/
		//If mosfet was off, then the new phase will be activated on the next pwm interrupt,
		//	no need to do anything extra
		pwm_pin_select = CL; //Set pwm lowside C
	  	break;
	case 6:
		//ADMUX = ADC_B;
		
		BH_OFF();
		AH_ON();
	  	break;
	}
}
