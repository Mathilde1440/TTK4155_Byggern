
#include <stdio.h>
#include <avr/io.h>



#include "uart.h"
#include "sram.h"
#include "labdag1.h"
#include "labdag2.h"
#include "labdag3.h"
#include "joystick.h"
#include "adc.h"
#include "SPI.h"
#include "oled.h"
#include "menu_interface.h"
#include "CAN_controller.h"
#include "gameplay.h"

#include <util/delay.h>






#define BAUD 9600UL
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1) 



int main(void) {

   // printf("Hei\n\r");

    ADC_read(0x0000);
    USART_Init(MYUBRR);
    SRAM_init();
    clk_adc_init();
    SPI_init();
    oled_init_2();
    oled_reset();

    CAN_init(MODE_NORMAL);

    oled_anti_clean();
    //test_CAN_transmitt_and_recieve();
    //test_CAN_transmitt_and_recieve_2();
    //CAN_controller_reset();
    //_delay_ms(10);
    //slave_select_test_CAN_2();
    //CAN_change_mode(MODE_LOOPBACK);
    //test_base_commands();
    //can_setup_loopback(void);
    //test_can_controller_reset();
    //test_RTS();
    //test_bit_modify();

    //test_CAN_transmitt_to_node_2();
    //test_CAN_transmitt_to_node_2();

    int lives = 5;

    int count = 0;




    while(1){

        count++;

        //if (count < )

        //oled_write_string("Spill et Spill", 4, 30);


        //if (count > 1000){



        //}

        
        


        IO_BOARD obj = read_analog_values_dir_IO();
        CAN_MESSAGE_FRAME msg;

        int recieved_lives = recieve_lives();
        //printf("Recieved message: %i\n\r", recieve_lives);
        if (recieved_lives != 40)
        {
                lives = recieved_lives;
                oled_anti_clean();

        }
    


        printf("lives %i \n\r", lives);

        oled_render_lives(lives);


        back_to_menue(&obj, lives);

        



        test_JS_driver(&obj, &msg);
    }




    //CAN_controller_reset();
    _delay_ms(2);






    
}
