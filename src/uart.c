#include <string.h>
#include <avr/interrupt.h>
#include "chipselect.h"
#include "uart.h"

#define UBRR_VAL	((F_CPU / 16 / BAUD_RATE) - 1)
#define TX_IDLE()	( UCSRA & (1 << UDRE) ) //non zero when data can be written to uart

volatile char outbuf[OUTBUFSIZE];
volatile uint8_t buf_head, buf_tail, buf_space;

ISR(USART_UDRE_vect)
{
    if (buf_space < OUTBUFSIZE)
    {
    	//load next char from buffer
        UDR = outbuf[buf_head++];
        //adjust tracking variables
        buf_head %= OUTBUFSIZE;
    	++buf_space;
    }
}

void uart_init(void)
{
    UCSRB |= (1 << TXEN) | (1 << UDRIE);
    UBRRH = (UBRR_VAL >> 8);
    UBRRL = UBRR_VAL;
    buf_head = 0;
    buf_tail = 0;
    buf_space = OUTBUFSIZE;
}

void uart_putchar(char c)
{
	if (TX_IDLE()) {
		//If tx is idle, bypass the buffer
        UDR = c;
	}
	else {
        //add to the buffer if it has room
        if (buf_space > 0) {
		    outbuf[buf_tail++] = c;
		    buf_tail %= OUTBUFSIZE; //circular buffer, wraps around to 0
		    --buf_space;
        }
	}
}

void uart_putstr(char* s)
{
    uint8_t i;
    if ((strlen(s) <= buf_space) && (strlen(s) > 0))
    {
    	i = 0;
        while (s[i]) //read everything until the null char
        {
		    outbuf[buf_tail++] = s[i]; //add to buffer
		    buf_tail %= OUTBUFSIZE; //circular buffer, wraps around to 0
		    --buf_space;
            i++; //next char
        }
        if (TX_IDLE())
        {
            //if tx is idle, kick start transmission
            //the UDRE interrupt will continue reading the buffer
		    UDR = outbuf[buf_head++];
		    buf_head %= OUTBUFSIZE;
			++buf_space;
        }
    }
}

void uart_putint(int n)
{
	// Converts an int to a string and put in uart buffer
    if (buf_space >= 9)
    {
		char temp[6], s[9];
		uint8_t digits=0, i=0, j=0;
		
		memset(temp, '\0', 6);
		memset(s, '\0', 9);
		
		if (n < 0) {
		    digits++; //count negative sign as a digit, as it takes up a char
			s[j++] = '-';
			n = -n;
		}
		//count num of digits while filling temp buffer
		while (n > 0) {
			digits++;
			temp[i++] = '0' + (n % 10);
			n /= 10;
		}
		i--;
		//number is in reverse string order, correct it
		while (j < digits) {
			s[j++] = temp[i--];
		}
		s[j++] = '\n';
		s[j++] = '\r';
	
		uart_putstr(s);
	}
}
