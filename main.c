

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
#include "SPI.h"
#include "oled.h"





#define BAUD 9600UL
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1) 



int main(void) {
    ADC_read(0x0000);
    USART_Init(MYUBRR);
    SRAM_init();
    clk_adc_init();

    SPI_init();
    oled_init_2();
    oled_anti_clean();
    _delay_ms(1000);
    oled_clear_column(3);
    _delay_ms(1000);
    _delay_ms(1000);
    oled_reset();




    //slave_select_test_OLED();
    //slave_select_test_IO();
    //DC_select_test();
    //oled_init();
    //turn_light_on(2);
    //flashing_lights_2();
    //flashing_lights();
    //flashing_lights_3();
    //clear_all_lights();

    
}
