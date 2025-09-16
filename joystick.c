#include "joystick.h"
#include "adc.h"




IO_BOARD read_analog_values_dir_IO()
{
    IO_BOARD IO_BOARD_obj;

    IO_BOARD_obj.X_JS = ADC_read(JOYSTICK_DIR_X);
    IO_BOARD_obj.Y_JS = ADC_read(JOYSTICK_DIR_Y);
    IO_BOARD_obj.X_TP = ADC_read(TOUCHPAD_DIR_X);
    IO_BOARD_obj.Y_TP = ADC_read(TOUCHPAD_DIR_Y);

    return IO_BOARD_obj;

} 

IO_BOARD convert_position_percent(IO_BOARD IO_BOARD_obj){
    double a_JS = (200/3);
    double b_JS = (-500/3);
    double a_TP = 40;
    double b_TP= (-100);

    IO_BOARD_obj.X_JS = a_JS*IO_BOARD_obj.X_JS + b_JS;
    IO_BOARD_obj.Y_JS = a_JS*IO_BOARD_obj.Y_JS + b_JS;
    IO_BOARD_obj.X_TP = a_TP*IO_BOARD_obj.X_TP + b_TP;
    IO_BOARD_obj.Y_TP = a_TP*IO_BOARD_obj.Y_TP + b_TP;

    return IO_BOARD_obj;
}

JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD IO_BOARD_obj)
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

void test_function_JS(JOYSTICK_DIRECTION direction){

   

    if ( direction == UP){

        printf( "Direction is UP \n");
    }
    if ( direction == DOWN){

        printf( "Direction is DOWN \n");
    }
    if ( direction == LEFT){

        printf( "Direction is LEFT \n");
    }
    if ( direction == RIGHT){

        printf( "Direction is RIGHT \n");
    }
    if ( direction == NEUTRAL){

        printf( "Direction is Neutral \n");
    }

}