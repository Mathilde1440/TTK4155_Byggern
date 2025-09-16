

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"
#include "labdag2.h"
#include "labdag3.h"
#include "joystick.h"
#include "adc.h"




#define BAUD 9600UL
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1) 



int main(void) {
    ADC_read(0x0000);
    
    

    USART_Init(MYUBRR);

    //while (1){
    
        //test_med_echo();
     
        //printf("ing");  //printf

        //test_for_latch();
    //}

    SRAM_init();
    //SRAM_test();
    clk_adc_init();
    //while(1){
        //_delay_ms(2000);
        //adc_kick();
        
        //volatile v = adc_read0();
        //_delay_ms(2000);
        //void(v);
        
    //}
    IO_BOARD testobject;
    JOYSTICK_DIRECTION dir;

    while (1)
    {
     testobject = read_analog_values_dir_IO();
     testobject = convert_position_percent(testobject);
     dir = get_JS_DIR(testobject);
     test_function_JS(dir);

     _delay_ms(2000);
     
    }
    

    
    
}
