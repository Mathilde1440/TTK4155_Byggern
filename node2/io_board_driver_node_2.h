
#ifndef IO_BOARD_DRIVER_NODE_2_H_
#define IO_BOARD_DRIVER_NODE_2_H_

#include <stdint.h>
#include "can_controller.h"

typedef struct {
    uint8_t X_JS;
    uint8_t Y_JS;

    int8_t X_JS_PRC;
    int8_t Y_JS_PRC;

} IO_BOARD;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} JOYSTICK_DIRECTION;

void convert_position_percent(IO_BOARD* IO_BOARD_obj);
JOYSTICK_DIRECTION get_JS_DIR(IO_BOARD* IO_BOARD_obj);

void print_IO_BOARD_obj(IO_BOARD* obj);

IO_BOARD transform_CAN_msg_to_IO_BOARD_obj(CAN_MESSAGE* msg, IO_BOARD* obj);

void test_function_JS(JOYSTICK_DIRECTION direction);




#endif 