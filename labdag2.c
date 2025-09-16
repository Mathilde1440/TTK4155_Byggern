#include "labdag2.h"
#include <util/delay.h>



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

        //PORTC = 0b00000111;  //ADC
        PORTC = 0b00001111; //SRAM

        PORTE = 0b00;

       

        PORTE = 0b10;
        
}


void SRAM_write(uint8_t data,uint16_t address){
        volatile char *ext_mem = (char *) SRAM_start;
        ext_mem[address] = data;
}

uint8_t SRAM_read(uint16_t address)
{    
        volatile char *ext_mem = (char *) SRAM_start;
        uint8_t ret_val = ext_mem[address];
        return ret_val;
}

void ADC_write(uint8_t data,uint16_t address){
        volatile char *ext_mem = (char *) ADC_start;
        ext_mem[address] = data;
}



void test_for_decoder_2()
{
        while(1){
        SRAM_write(0xA5,0x0001);
        SRAM_read(0x0001);
        
        _delay_ms(2000);

        ADC_write(0x5A,0x0001);
        ADC_read(0x0001);
        }
}
