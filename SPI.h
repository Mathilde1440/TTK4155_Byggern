#ifndef SPI_H
#define SPI_H


#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>



#define OLED_SS 0
#define IO_board_SS 1
#define RW_COMMAND 0
#define RW_DATA 1



void SPI_init();
void Slave_select(int n);
void Reset_slave_select(int n);
void set_DC(int i);
void SPI_write(uint8_t data);
uint8_t SPI_read();

//test functions
void slave_select_test_OLED();
void slave_select_test_IO();
void DC_select_test();


void light_on(int LED_N);
void light_of(int LED_N);
void flashing_lights();
void flashing_lights_2();
void flashing_lights_3();


#endif