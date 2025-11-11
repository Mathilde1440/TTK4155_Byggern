#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>
#include <util/delay.h>

#include "CAN_controller.h"
//#include "labdag3.h"


#define NUM_CHANNELS_ADC 4
#define JOYSTICK_DIR_X 0       //Joystick_X koblet til AIN3
#define JOYSTICK_DIR_Y 1        //Joystick_Y koblet til AIN2
#define TOUCHPAD_DIR_X 2        //Touchpad_x koblet til AIN1
#define TOUCHPAD_DIR_Y 3        //Touchpad_y koblet til AIN0


typedef struct {
    uint8_t X_JS;
    uint8_t Y_JS;
    uint8_t X_TP;
    uint8_t Y_TP;

    int8_t X_JS_PRC;
    int8_t Y_JS_PRC;
    int8_t X_TP_PRC;
    int8_t Y_TP_PRC;

    int8_t JS_button_pressed;


} IO_BOARD;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} JOYSTICK_DIRECTION;

IO_BOARD read_analog_values_dir_IO();
IO_BOARD convert_position_percent(IO_BOARD IO_BOARD_obj);
JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD IO_BOARD_obj);



JOYSTICK_DIRECTION get_JS_DIR_first(IO_BOARD IO_BOARD_obj);

JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD IO_BOARD_obj);
JOYSTICK_DIRECTION get_TP_DIR(IO_BOARD IO_BOARD_obj);
int JS_button_pressed();


void test_function_JS(JOYSTICK_DIRECTION direction);
void test_function_TP(JOYSTICK_DIRECTION direction);

void encode_JS_direction(IO_BOARD* obj, CAN_MESSAGE_FRAME* msg);


void joystic_test();

//uint8_t* ADC_read_testing();
#endif

void test_JS_driver(IO_BOARD* obj, CAN_MESSAGE_FRAME* msg);