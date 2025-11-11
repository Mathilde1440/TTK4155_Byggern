#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "io_board_driver_node_2.h"

typedef enum {
    STILL = 500,
    SLOW = 5, //30
    MEDIUM = 3, //40
    FAST = 2 //50

} MOTOR_SPEED_SCALER;

typedef enum {

    M_LEFT,
    M_RIGHT

} MOTOR_DIRECTION;


typedef enum {
    STILL_PRC = 0,
    SLOW_PRC = 30, //30
    MEDIUM_PRC = 40, //40
    FAST_PRC = 50 //50

} MOTOR_SPEED_SCALER_PRC;


void set_speed_and_direction_2(double DC, MOTOR_DIRECTION dir);
void motor_init();
void set_direction_and_speed(IO_BOARD* obj);

void set_motor_direction( MOTOR_DIRECTION dir);

void motor_driver_test_1();
void set_speed(double DC);


#endif