

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
#include "menu_interface.h"
#include "CAN_controller.h"






#define BAUD 9600UL
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1) 



int main(void) {
    ADC_read(0x0000);
    USART_Init(MYUBRR);
    SRAM_init();
    clk_adc_init();
    SPI_init();
    oled_init_2();
    oled_reset();

    CAN_init(MODE_LOOPBACK);
    //test_CAN_transmitt_and_recieve();
    //CAN_controller_reset();
    //_delay_ms(10);
    //slave_select_test_CAN_2();
    //CAN_change_mode(MODE_LOOPBACK);
    //test_base_commands();
    //can_setup_loopback(void);
    //test_can_controller_reset();
    //test_RTS();
    //test_bit_modify();


    //CAN_controller_reset();
    _delay_ms(2);






    
}
