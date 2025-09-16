#include "adc.h"
#include <util/delay.h>


void clk_adc_init(void){
    DDRD |= (1 << PD5);
    //DDD5 |= 5;
    TCCR1A = (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << WGM13);
    TCCR1A |= (1 << COM1A0);

    OCR1A = 10;      
                      
    TCCR1B |= (1 << CS10); 

}


volatile uint8_t ADC_read(uint16_t address){
        volatile char *ext_mem = (char *) ADC_start;
        ext_mem[0] = 0;
        
        //delay transmisson when the ADC is converting, time found in the data sheet
        _delay_ms((9*NUM_CHANNELS_ADC*2)/F_CPU);

        uint8_t ret_val = 0;
        for (int i = 0; i <= address; ++i){
            ret_val = ext_mem[0];
        }

        //uint8_t ret_val = ext_mem[address];
        return ret_val;
}