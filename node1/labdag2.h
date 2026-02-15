#ifndef LABDAG2_H
#define LABDAG2_H

#include <avr/io.h>

#include "uart.h"
#include "sram.h"
#include <stdio.h>


#define SRAM_start 0x1800
#define SRAM_stop 0x1FFF


void test_for_latch();
void test_for_decoder();

void SRAM_write(uint8_t data,uint16_t address);
uint8_t SRAM_read(uint16_t address);
void ADC_write(uint8_t data,uint16_t address);


#endif