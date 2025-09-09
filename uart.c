#include "uart.h"
#include <stdio.h>

//dette er hentet direkte fra databladet til AtMega

void USART_Init( unsigned int ubrr )
{

    //UCSR0A = (1 << U2X0);   // bruk dobbel hastighet ....
    UCSR0A = 0;            
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;


    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);


    /* Set frame format: 8data, 2stop bit */
    //UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
    UCSR0C = (1<<URSEL0)|(1<<UCSZ01)|(1<<UCSZ00);

//attempt to fix printf
    fdevopen(USART_Transmit, USART_Receive);
}

int USART_Transmit(char data, FILE * file )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
        ;

    /* Put data into buffer, sends the data */
    UDR0 = data;
    return 0;
}

int USART_Receive( FILE * file )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

