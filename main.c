
#include <stdio.h>
#include <avr/io.h>



#include "node1/uart.h"
#include "node1/sram.h"
#include "node1/labdag1.h"
#include "node1/labdag2.h"
#include "node1/labdag3.h"
#include "node1/joystick.h"
#include "node1/adc.h"
#include "node1/SPI.h"
#include "node1/oled.h"
#include "node1/menu_interface.h"
#include "node1/CAN_controller.h"

#include <util/delay.h>






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
    test_CAN_transmitt_and_recieve_2();
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
