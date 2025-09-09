#ifndef UART_H
#define UART_H
#define F_CPU 4915200UL


#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>





void USART_Init( unsigned int ubrr );             // 8N1, async, no parity
int USART_Transmit(char data, FILE * file  ); // blokkerende send
//int USART_Transmit( unsigned char data, FILE * file  ); 
int USART_Receive(FILE * file  );     // blokkerende mottak
//unsigned char USART_Receive( void ); 


//void uart_send_string(const char *s);

#endif
