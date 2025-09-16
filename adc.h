#ifndef ADC_H
#define ADC_H


#include <avr/io.h>

#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"
#include "labdag2.h"
//#include "joystick.h"

#define ADC_start 0x1000
#define ADC_stop 0x17FF

void clk_adc_init(void);
volatile uint8_t ADC_read(uint16_t address);

#endif