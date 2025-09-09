#include "labdag2.h"



void test_for_latch(){
        DDRE = 0b10;   //  test for latch
        DDRA = 0b11111111;
        

        PORTE = 0b10;
        PORTA = 0b00000010;

        _delay_ms(2000);

        PORTE = 0b00;

        _delay_ms(2000);

        PORTE = 0b10;
        PORTA = 0b00000000;
        PORTE = 0b00;
        _delay_ms(2000);

        PORTE = 0b01;

}

void test_for_decoder(){
        DDRE = 0b10;   //  test for latch
        DDRA = 0b11111111;
        DDRC = 0b11111111;
        

        PORTE = 0b10;

        PORTC = 0b00000111;  //ADC
        //PORTC = 0b00001111; //SRAM

        PORTE = 0b00;

       

        PORTE = 0b10;
        

        

}