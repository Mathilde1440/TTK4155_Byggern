#include "labdag3.h"
#include <util/delay.h>

#define ADC_BASE ((volatile uint8_t*)0x1000)

void adc_kick(void)   
{ 
    ADC_BASE[0] = 0x00; 

} 
uint8_t adc_read0(void)
{ 
    return ADC_BASE[0]; 

} 




