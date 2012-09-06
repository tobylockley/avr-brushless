#include <avr/interrupt.h>

#include "chipselect.h"
#include "powerstage.h"
#include "tones.h"
#include "uart.h"

#define delay_count (F_CPU / 100000UL)

void delay(uint8_t ms)
{
    uint16_t cnt;
    asm volatile(
        "\n"
        "L_dl1%=:" "\n\t"
        "mov %A0, %A2" "\n\t"
        "mov %B0, %B2" "\n"
        "L_dl2%=:" "\n\t"
        "sbiw %A0, 1" "\n\t"
        "brne L_dl2%=" "\n\t"
        "dec %1" "\n\t"
        "brne L_dl1%=" "\n\t"
        : "=&w" (cnt)
        : "r" (ms), "r" (delay_count)
    );
}

int main(void)
{
    DDRB |= (1 << PB1);
    //check if power reset happened
    if (MCUSR & (1 << PORF)) {
        PORTB |= 1 << PB1;
    }
    MCUSR = 0;

    ///
    ADMUX = (1<<ADLAR) | (1<<REFS0);
    ADCSRA = (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //prescl 128
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
    ///

    powerstage_init();
    uart_init();

    sei(); //Enable global interrupts

    //tone_low();
    //tone_med();
    //tone_high(); //Tone to signify end of initialisation
    delay(250);
    delay(250);
    delay(250);
    delay(250);

    //set_pwm(0.04*PWM_RANGE);
    //startDC();
    PORTB |= (1<<PB1);

    while(1) {
        //commutate_motor();
        //set_pwm(ADCH);
        delay(5);
    }
}
