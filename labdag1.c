#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"





void test_med_echo(){
    USART_Transmit('i', NULL); // transmitts a contious stream of "i"-s from the MCI
        _delay_ms(1000);

         if (UCSR0A & (1 << RXC0)) { //test for MCI to echo keyboard input
         unsigned char c = USART_Receive(NULL);
         USART_Transmit(c, NULL);
         if (c == '\r' || c == '\n') { USART_Transmit('\r', NULL); USART_Transmit('\n', NULL); }
     }
}

void firkantpuls(){
    // Sett PB1 som utgang
    DDRB |= (1 << PB1);

    while (1) {
        PORTB ^= (1 << PB1);   // toggle PB1
        _delay_ms(50);
    }
}