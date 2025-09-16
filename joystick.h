

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"
#include "labdag2.h"
//#include "labdag3.h"


#define NUM_CHANNELS_ADC 4
#define JOYSTICK_DIR_X 0
#define JOYSTICK_DIR_Y 1
#define TOUCHPAD_DIR_X 2
#define TOUCHPAD_DIR_Y 3


typedef struct {
    uint8_t X_JS;
    uint8_t Y_JS;
    uint8_t X_TP;
    uint8_t Y_TP;
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
void test_function_JS(JOYSTICK_DIRECTION direction);
