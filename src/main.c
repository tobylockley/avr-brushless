#include <avr/interrupt.h>
#include <util/delay.h>

#include "chipselect.h"
#include "powerstage.h"
#include "tones.h"
#include "uart.h"

int main(void)
{	
	//check if power reset happened
	DDRB |= (1 << PB1);
	if (MCUSR & (1 << PORF)) PORTB |= 1 << PB1;
	MCUSR = 0;
	
	powerstage_init();
	uart_init();
	    
	sei(); //Enable global interrupts
	
	//set_pwm(6);
	
	tone_low();
	tone_med();
	tone_high();
	
	while(1) {
	}
}
