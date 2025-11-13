#include "uart.h"
#include <stdio.h>

//USAR_iinit, transmitt og recieve er hentet direkte fra databladet til AtMega s. 172
//https://learn-eu-central-1-prod-fleet01-xythos.content.blackboardcdn.com/5def77a38a2f7/309080?X-Blackboard-S3-Bucket=learn-eu-central-1-prod-fleet01-xythos&X-Blackboard-Expiration=1763078400000&X-Blackboard-Signature=d4CPdGHD12lNx0oVlgU39Ferjg75eSirLcHMOGujChQ%3D&X-Blackboard-Client-Id=303508&X-Blackboard-S3-Region=eu-central-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27Microcontroller%2520ATmega162.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEIn%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaDGV1LWNlbnRyYWwtMSJGMEQCIFjQjNsdbpp0plwdXi%2BVNhF2TVNiPJeGBNExHb%2BWfUB8AiAAlh7o5Bp9Fqx3FucZt6QzsKbm6Uw4EVt2KBFpik7wliq%2BBQhSEAQaDDYzNTU2NzkyNDE4MyIMbCC3xB8yU%2BWBCH2SKpsFsGGczVdATfWJMUr4oZZupUvtxE2%2B%2BAfiMpF4cDHpfeE8f81FxJoyoAgDeujEAyhHmfCaXo3QpSUt%2B30guvkEGvKr0PZAmqOUfs17d9jT75DEvJIYx%2Fav2fZhzY8i67cJsZNgrzdNBQrYHfO6OS4Hg4j095tWP7oot9DwXPoBVIEC%2FdmkcB0se0lme8uScUsFuw20x0cGEWT61b%2BTA%2Byq11uz%2BvuGnTyT9vQ%2BLv1u0aDcb6Zgb5R210H4nkUzsM6wp0a8BWd8makko3UwlIT%2F3dw4Xt2dWT4YYdXUYzCRyZcE6XKXNWJ4pAcsTuNemr7VDtDNRhKKiZh1KIzg8F6kRxp%2B8nQMj7Q%2BEIHh0SIS8lM2Slr7iwleeYmjLGbnw5AN31P1dlrQ3WE12VIGiF7rUYBlWjMg7KEPJB6bciQOeH1o0XDP3QRUtmeyfltDZ%2FeRfeoI7bYFfygjcVFYZervu%2FmhUwuOQ3OwZVA7ARvqWHrXsJlGXurL9AsR11u4AFSh7gjuxSrsXTexQUo8qh%2FMWE7VBE2p7QIx4T5F3o1O1FGKLNRdtHxpswGNPqC%2ByJeUkq5K0YCKCY%2FsNfsRDKRxN8QXM%2BIU3kI1%2B6oEF1XS8jc7twH17BiX%2BD%2FaTAwRiPdZ4hg8IK2fdVGSagi%2BCNT4illYDPCzX1axubZPTc9MAeDfi6ByYyqDc2Yz7oZJBoyNJjMXylS8Z%2FVKl%2FmxEBJUlceAr0I9DScaj4y%2BFhTLavVSUrOpdl3UwKwG0sGeTJKGDs8oqxPBcnTKgNiEoPCmnC%2F0Gk0xwIyWbcXDmSVYSEk4qw1W2WbBlKT8LNtY8ELRBNNNUjTw6OAfOJ5pRSPqo7Wg2wrWz6KWn91T8iOZBeJLUM40SOIllYcgpDCLn9jIBjqyAc%2FwPnZOJMFbMWklhZJ8eLMTM%2BDAN1xotcq88BRXVc2prvElEEFZVIBtodxFaBoK7SQtYQaIlTYePPtczBpwFmFKT7c28t9cese0Ic0QaJb4%2B5KyGBHqIjqnkW8i9CItFbuNLmj7hIgXo3AzOn5cuKUEOrBlTIft%2FcMyvh%2Fjq%2BiNR5tsUD01nEYS0kObQmzTy4Z%2FBriYRAL5xQambrbiqKNcwAUx6ckGwvj2o6xFbI7YF48%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20251113T180000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLV5UP3K2L%2F20251113%2Feu-central-1%2Fs3%2Faws4_request&X-Amz-Signature=23ac3798a5ca044e0d03618bc1ea2a907794a559787a40b6a6a4de61887c9b81

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

