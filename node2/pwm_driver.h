#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#define PWM_D_MIN 900u
#define PWM_D_MAX 2100u

void timer_counter_init();

uint32_t clamp_signal(uint32_t signal,uint32_t lower_bounds, uint32_t uppper_bounds);

void calulate_and_set_DC(int8_t direction);

void set_DC(uint32_t duty_cycle);

#endif
