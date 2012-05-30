#ifndef _UART_H_
#define _UART_H_

#define BAUD_RATE 9600
#define OUTBUFSIZE 64 //Can be any value between 1-255

void uart_init(void);
void uart_putchar(char c);
void uart_putstr(char* s);
void uart_putint(int n);

#endif /* _UART_H_ */
