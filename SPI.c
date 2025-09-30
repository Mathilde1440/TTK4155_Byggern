#include "SPI.h"

#include <util/delay.h>


void SPI_init(){
    //conigure all in- and output pins
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB4); // set slave salect OLED as an Output 
    DDRB |= (1 << PB3); // set slave salect IO_board as an Output 
    DDRB |= (1 << PB5); 
    DDRB &= ~(1<< PB6); 
    DDRB |= (1 << PB7); 

    SPCR &= ~(1 << CPOL);
    SPCR &= ~(1 << CPHA);

    Reset_slave_select(OLED_SS); // Precaution, makes sure no salve is selectet 
    Reset_slave_select(IO_board_SS);
    set_DC(0); // somhow this only works when tis is set in the init function. Does not matter if it is set to zero or 1
  

    SPCR |= (1 << SPE); // Enable SPI?
 

    SPCR |= (1 << MSTR); //Supposed to configure the atmega as the master
 
    
    

    //DORD |=  1; // LSB is pushed first, when cahnged to zero MSB will be pushed firt. Might have to be changed

    SPCR |= (1 << SPR0);
   

    //set to SPI mode 0 : Leading edge rising(CPOL = 0) and  sample on leading edge (CPHA = 0) for lab lecture
}
void Slave_select(int n){
    switch (n)
    {
    case 0: // set SS to zero for the Oled display, and chooses the OLed display as the salev
        PORTB &= ~(1 << PB4); 
        PORTB |= (1 << PB3); 
        break;
    case 1: // set SS to zero for the Oled display, and chooses the OLed display as the salev
        PORTB &= ~(1 << PB3); 
        PORTB |= (1 << PB4); 
        break;
    
    default:
        break;
    }
}

void Reset_slave_select(int n){
    switch (n)
    {
    case 0: // set SS to zero for the Oled display, and chooses the OLed display as the salev
        PORTB |= (1 << PB4); 
        break;
    case 1: // set SS to zero for the Oled display, and chooses the OLed display as the salev
        PORTB |= (1 << PB3); 
        break;    
    
    default:
        break;
    }

}
void set_DC(int i){
    switch (i)
    {
    case 0: //Indicates COMMAND Read/Write
        PORTB &= ~(1 << PB2); 
        break;
    case 1: //Indicates DATA Read/Write
        PORTB |= (1 << PB2); 
        break;    
    
    default:
        break;
    }
}
void SPI_write(uint8_t data){
    
    SPDR = data;
    while (! ( SPSR & (1 << SPIF))){}; // waits for transmission to finish
    //(void)SPSR; (void)SPDR;

}
uint8_t SPI_read(){
    SPDR = 0x00; //kicks" the SPI data registerr and starts transmission
    while (! ( SPSR & (1 << SPIF))){}; // waits for transmission to finish
    (void)SPSR;
    return SPDR;

}

void slave_select_test_OLED()
{
    while(1){
        Slave_select(OLED_SS);
        _delay_ms(10000);
        Reset_slave_select(OLED_SS);
        _delay_ms(10000);  
    }
}

void slave_select_test_IO()
{
    while (1)
    {
        Slave_select(IO_board_SS);
        _delay_ms(10000);
        Reset_slave_select(IO_board_SS);
        _delay_ms(10000);
    }
    
}

void DC_select_test()
{
    while (1)
    {
        set_DC(RW_COMMAND);
        _delay_ms(10000);
        set_DC(RW_DATA);
        _delay_ms(10000);
    }
    
}

void light_on(int LED_N){
    Slave_select(IO_board_SS);
    _delay_us(2);  
    SPI_write(0x05);
    _delay_us(40); 
    SPI_write(LED_N);
    SPI_write(0x001);
    _delay_us(2);  
    Reset_slave_select(IO_board_SS);   
    _delay_us(50);  

}
void light_of(int LED_N){
    Slave_select(IO_board_SS);
    _delay_us(2);  
    SPI_write(0x05);
    _delay_us(40); 
    SPI_write(LED_N);
    SPI_write(0x000);
    _delay_us(2);  
    Reset_slave_select(IO_board_SS);
    _delay_us(50);  
    
}

void flashing_lights()
{
    while(1){
        //Slave_select(IO_board_SS);
    
        //SPI_write(0x05);
        //_delay_us(40); 
        //SPI_write(0x01);
        //SPI_write(0x01);
         //Reset_slave_select(IO_board_SS);
        
        //_delay_ms(10000);
      
        Slave_select(IO_board_SS);
        SPI_write(0x05);
        _delay_us(40); 
        SPI_write(0x01);
        SPI_write(0x00);
        
      
        Reset_slave_select(IO_board_SS);
    
        
    }

}

void flashing_lights_2(){

    while(1){
        light_on(3);

        _delay_ms(500);
        light_of(3);
        _delay_ms(1000);
    }


}


void flashing_lights_3(){

    while(1){
        for(int i = 0; i < 6; i++)
        {
            light_on(i);
            _delay_ms(1000);
        }
        for(int j = 0; j < 6; j++)
        {
            light_of(j);
            _delay_ms(1000);
        }

}
}