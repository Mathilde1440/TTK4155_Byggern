#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "uart.h"
#include "can_controller.h"
#include "test_functions_can.h"
#include "io_board_driver_node_2.h"
#include "pwm_driver.h"
#include "adc.h"
#include "encoder.h"
#include "PI_controller.h"
#include "motor_driver.h"
#include "solenoid_driver.h"
#include "play_game.h"





#include "sam3xa.h"


/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"

#define F_CPU 84000000
#define BAUD 9600


int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    IO_BOARD obj_1;
    IO_BOARD obj_2;





   
    uart_init(F_CPU, BAUD);
    can_init_def_tx_rx_mb(0x00293255); //BRP, SJW, PROPAG PHASE1,PHASE2
    timer_counter_init();
    adc_init();
    encoder_init();
    counter_init();
    motor_init();
    solenoid_init();


    //test_keep_score();
    //while(1) {
    //recieve_io_obj(&obj_1, &obj_2);
    //printf("hei");

    //while(1){

        //transmitt_lives();

   // }


    
    //int32_t enc_pos = read_encoder_pos();

    play_game();
    //transmitt_lives();

    test_can_transmitt();


    //test_PI_controller(&obj_1, &obj_2);
    //printf("Encoder pos: %i \n\r", enc_pos);
    //test_servo_driver();
    //test_counter();
    //test_keep_score();
    //set_speed_and_direction_2(-50);
    //}
    

    //test_servo_driver();
    //calulate_and_set_DC(100);
    //test_adc_read();
    //test_JS_driver();
}
//TC_CV0 s876 posisjon kan leses her ifra 32bit ord
//POSEN bit in TC_BMR -> position prcessesd on ch 0, # motorrevolutions read at can 1
//