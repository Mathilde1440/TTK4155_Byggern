#include "joystick.h"
#include "adc.h"
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"
#include "labdag2.h"




IO_BOARD read_analog_values_dir_IO()
{
    IO_BOARD IO_BOARD_obj;

    //IO_BOARD_obj.X_JS = ADC_read(JOYSTICK_DIR_X);
    //IO_BOARD_obj.Y_JS = ADC_read(JOYSTICK_DIR_Y);
    //IO_BOARD_obj.X_TP = ADC_read(TOUCHPAD_DIR_X);
    //IO_BOARD_obj.Y_TP = ADC_read(TOUCHPAD_DIR_Y);

    //IO_BOARD_obj.Y_TP = ADC_read(JOYSTICK_DIR_X);
    //IO_BOARD_obj.Y_JS = ADC_read(TOUCHPAD_DIR_X);
    //IO_BOARD_obj.X_TP = ADC_read(JOYSTICK_DIR_Y);
    //IO_BOARD_obj.X_JS = ADC_read(TOUCHPAD_DIR_Y);
    uint8_t array[4] = {0,0,0,0};
    ADC_read_testing(array);
    IO_BOARD_obj.Y_TP = array[0];
    IO_BOARD_obj.Y_JS = array[1];
    IO_BOARD_obj.X_TP = array[2];
    IO_BOARD_obj.X_JS = array[3];

    //uint8_t *a = ADC_read_testing();
    //printf("_other_fubction %d \n", a);
    //
    //printf("Joystick_X: %d Joystick_Y: %d Tuchpad_X: %d Tuchpad_Y: %d \n\r", IO_BOARD_obj.X_JS,IO_BOARD_obj.Y_JS,IO_BOARD_obj.X_TP,IO_BOARD_obj.Y_TP);


    return IO_BOARD_obj;

} 

IO_BOARD convert_position_percent(IO_BOARD IO_BOARD_obj)
{
    IO_BOARD testobject_prc;
    double a_JS = (100.0/87.0);
    double b_JS = (-15800.0/87.0);
    double a_TP = (200.0/253.0);
    double b_TP= (-25700.0/253.0);

    testobject_prc.X_JS_PRC = a_JS*IO_BOARD_obj.X_JS + b_JS;
    testobject_prc.Y_JS_PRC = a_JS*IO_BOARD_obj.Y_JS + b_JS;
    testobject_prc.X_TP_PRC = a_TP*IO_BOARD_obj.X_TP + b_TP;
    testobject_prc.Y_TP_PRC = a_TP*IO_BOARD_obj.Y_TP + b_TP;
    //printf("Joystick X : %d, org_value: %d, Joystick Y : %d \n\r", testobject_prc.X_JS_PRC, IO_BOARD_obj.X_JS, testobject_prc.Y_JS_PRC);
    //printf("tp X : %d, org_value: %d,       TP Y : %d \n\r", testobject_prc.X_TP_PRC, IO_BOARD_obj.X_TP, testobject_prc.Y_TP_PRC);
    

    return testobject_prc;
}


JOYSTICK_DIRECTION get_JS_DIR_first(IO_BOARD IO_BOARD_obj)
{
    JOYSTICK_DIRECTION direction;

    if ( (IO_BOARD_obj.Y_JS > 5) && ( abs(IO_BOARD_obj.X_JS) >= IO_BOARD_obj.Y_JS) ){
        direction = UP;
    }
    else if ( ( IO_BOARD_obj.X_JS > 5) && ( abs(IO_BOARD_obj.Y_JS) >= IO_BOARD_obj.X_JS)  ){
        direction = RIGHT;
    }
    else if ( (IO_BOARD_obj.Y_JS < (-5)) && ( -abs(IO_BOARD_obj.X_JS) <= IO_BOARD_obj.Y_JS) ) {
        direction = DOWN;
    }
    else if ( (IO_BOARD_obj.X_JS < (-5)) && ( -abs(IO_BOARD_obj.Y_JS) <= IO_BOARD_obj.X_JS) ) {
        direction = LEFT;
    }
    else {
        direction = NEUTRAL;
    }
    
    return direction;
}

JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD IO_BOARD_obj)
{
    int neutral_dead_zone = 7;
    JOYSTICK_DIRECTION direction;

    if (abs(IO_BOARD_obj.Y_JS_PRC) >= abs(IO_BOARD_obj.X_JS_PRC) )
    {
        if ( abs(IO_BOARD_obj.Y_JS_PRC)  < neutral_dead_zone )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj.Y_JS_PRC > 0)
        {
            direction = UP;
        }
        else if (IO_BOARD_obj.Y_JS_PRC < 0)
        {
            direction = DOWN;
        }

    }

    else
    {
        if ( abs(IO_BOARD_obj.X_JS_PRC)  < neutral_dead_zone )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj.X_JS_PRC > 0)
        {
            direction = RIGHT;
        }
        else if (IO_BOARD_obj.X_JS_PRC < 0)
        {
            direction = LEFT;
        }

    }


    return direction;

}

JOYSTICK_DIRECTION get_TP_DIR(IO_BOARD IO_BOARD_obj)
{
    int neutral_dead_zone_TP = 20;
    JOYSTICK_DIRECTION direction;

    if (abs(IO_BOARD_obj.Y_TP_PRC) >= abs(IO_BOARD_obj.X_TP_PRC) )
    {
        if ( abs(IO_BOARD_obj.Y_TP_PRC)  < neutral_dead_zone_TP )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj.Y_TP_PRC > 0)
        {
            direction = UP;
        }
        else if (IO_BOARD_obj.Y_TP_PRC < 0)
        {
            direction = DOWN;
        }

    }

    else
    {
        if ( abs(IO_BOARD_obj.X_TP_PRC)  < neutral_dead_zone_TP )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj.X_TP_PRC > 0)
        {
            direction = RIGHT;
        }
        else if (IO_BOARD_obj.X_TP_PRC < 0)
        {
            direction = LEFT;
        }

    }


    return direction;

}

int JS_button_pressed(){
    return !( PINB & (1 << PB1));
}



void test_function_JS(JOYSTICK_DIRECTION direction){

   

    if ( direction == UP){

        printf( "Direction is UP \n\r");
    }
    if ( direction == DOWN){

        printf( "Direction is DOWN \n\r");
    }
    if ( direction == LEFT){

        printf( "Direction is LEFT \n\r");
    }
    if ( direction == RIGHT){

        printf( "Direction is RIGHT \n\r");
    }
    if ( direction == NEUTRAL){

        printf( "Direction is Neutral \n\r");
    }

}

void test_function_TP(JOYSTICK_DIRECTION direction){

   

    if ( direction == UP){

        printf( "Direction is UP \n\r");
    }
    if ( direction == DOWN){

        printf( "Direction is DOWN \n\r");
    }
    if ( direction == LEFT){

        printf( "Direction is LEFT \n\r");
    }
    if ( direction == RIGHT){

        printf( "Direction is RIGHT \n\r");
    }
    if ( direction == NEUTRAL){

        printf( "Direction is Neutral \n\r");
    }

}


void joystic_test(){
    IO_BOARD testobject;
    IO_BOARD testobject2;
    JOYSTICK_DIRECTION dir;

    while (1)
    {
     testobject = read_analog_values_dir_IO();
     testobject2 = convert_position_percent(testobject);
     dir = get_JS_DIR(testobject2);
     test_function_JS(dir);

     _delay_ms(50);
     
    }

}