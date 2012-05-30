#ifndef UART_H
#define UART_H

#include <string.h>
#include <avr/interrupt.h>
#include "chipselect.h"

#define BAUD_RATE 9600

#define OUTBUFSIZE 64 //Can be any value between 1-255

void usart_init(void);
void usart_putchar(char c);
void usart_putstr(char* s);
void usart_putint(int n);

#endif //#ifndef UART_H
