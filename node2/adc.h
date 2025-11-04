#ifndef ADC_H_
#define ADC_H_


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

void adc_init();

uint16_t adc_read(); //resolution for adc is 12-but, uint16 should suffice as return value

uint16_t keep_score(uint16_t old_score);

void test_adc_read();
void test_keep_score();


#endif
