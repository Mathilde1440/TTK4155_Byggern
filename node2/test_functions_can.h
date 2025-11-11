#ifndef TEST_FUNCTIONS_CAN_H_
#define TEST_FUNCTIONS_CAN_H_


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "can_controller.h"
#include "io_board_driver_node_2.h"


void print_message_object_node_2(CAN_MESSAGE* message);
void test_rec_node_1();
void test_JS_driver();
void test_servo_driver();
void recieve_io_obj(IO_BOARD* obj_1, IO_BOARD* obj_2);
void test_PI_controller(IO_BOARD* obj_1, IO_BOARD* obj_2);




#endif 