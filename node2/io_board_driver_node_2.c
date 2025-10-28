#include "io_board_driver_node_2.h"

#include "sam.h"
#include <stdio.h>


void convert_position_percent(IO_BOARD* IO_BOARD_obj)
{

    double a_JS = (100.0/87.0);
    double b_JS = (-15800.0/87.0);

    IO_BOARD_obj->X_JS_PRC = a_JS*IO_BOARD_obj->X_JS + b_JS;
    IO_BOARD_obj->Y_JS_PRC = a_JS*IO_BOARD_obj->Y_JS + b_JS;


    //Caps at abs(100) for safety 
    if (abs(IO_BOARD_obj->X_JS_PRC) > 100)
    {

        if ( IO_BOARD_obj->X_JS_PRC < -100)
            {
            IO_BOARD_obj->X_JS_PRC = -100;

            }
        if ( IO_BOARD_obj->X_JS_PRC > 100)
            {
            IO_BOARD_obj->X_JS_PRC = 100;

            }
        
    }

    if (abs(IO_BOARD_obj->Y_JS_PRC) > 100)
    {
        
        if ( IO_BOARD_obj->Y_JS_PRC < -100)
            {
            IO_BOARD_obj->Y_JS_PRC = -100;

            }
        if ( IO_BOARD_obj->Y_JS_PRC > 100)
            {
            IO_BOARD_obj->Y_JS_PRC = 100;

            }
        
    }
}

JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD* IO_BOARD_obj)
{
    int neutral_dead_zone = 7;
    JOYSTICK_DIRECTION direction;

    if (abs(IO_BOARD_obj->Y_JS_PRC) >= abs(IO_BOARD_obj->X_JS_PRC) )
    {
        if ( abs(IO_BOARD_obj->Y_JS_PRC)  < neutral_dead_zone )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj->Y_JS_PRC > 0)
        {
            direction = UP;
        }
        else if (IO_BOARD_obj->Y_JS_PRC < 0)
        {
            direction = DOWN;
        }

    }

    else
    {
        if ( abs(IO_BOARD_obj->X_JS_PRC)  < neutral_dead_zone )
        {
            direction = NEUTRAL;
        }
        else if ( IO_BOARD_obj->X_JS_PRC > 0)
        {
            direction = RIGHT;
        }
        else if (IO_BOARD_obj->X_JS_PRC < 0)
        {
            direction = LEFT;
        }

    }


    return direction;

}

void print_IO_BOARD_obj(IO_BOARD* obj)
{
    JOYSTICK_DIRECTION dir = get_JS_DIR(obj);

    printf("x_num %i, x_PRC %i, y_num %i, y_PRC %i \n\r", obj->X_JS, obj->X_JS_PRC, obj->Y_JS,  obj->Y_JS_PRC);

}

IO_BOARD transform_CAN_msg_to_IO_BOARD_obj(CAN_MESSAGE* msg, IO_BOARD* obj)
{
    
    
    obj->X_JS = msg->data[0]; 

    obj->Y_JS = msg->data[1]; 


    convert_position_percent(obj);

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
