#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "io_board_driver_node_2.h"

#include "motor_driver.h"


typedef struct {


    MOTOR_DIRECTION dir; 


} PI_CONT;


double calc_p_ref_lin(IO_BOARD obj);
uint32_t calc_p_ref(IO_BOARD* obj,int encoder_output);
double PI_controller(double Kp, double Ki, double p_ref, int encoder_output, PI_CONT* obj);

void counter_init();
void test_counter();


#endif