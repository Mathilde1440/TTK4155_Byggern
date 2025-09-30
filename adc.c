#include "adc.h"
#include <util/delay.h>
#include "joystick.h"
#include "string.h"



volatile uint8_t *ret_value = (uint8_t *) ADC_start;


void clk_adc_init(void){
    DDRD |= (1 << PD5);
    //DDD5 |= 5;
    TCCR1A |= (1 << WGM11) | (1 << WGM10);
    TCCR1B |= (1 << WGM13);
    //TCCR1B |= (0 << WGM12);
    //uint32_t =


    TCCR1A |= (1 << COM1A0);
    //TCCR1A |= (1 << COM1A1);

       
                      
    TCCR1B |= (1 << CS10); 
    //TCCR1B |= (1 << CS12); 
    //TCCR1B |= (1 << CS11); 


    OCR1A = 10;   

}


uint8_t ADC_read(uint8_t address){

        volatile char *ext_mem = (char *) ADC_start;
        ext_mem[0] = 0;
        
        //delay transmisson when the ADC is converting, time found in the data sheet
        //_delay_ms((9*NUM_CHANNELS_ADC*2)/F_CPU);
        //_delay_ms(30);


        uint8_t ret_val;
        for (int i = 0; i <= address; i++){
            ret_val = ext_mem[0];
        }

        //uint8_t ret_val = ext_mem[address];
        //int one = 1;
        //printf("Value out of adc %d", ret_val);
        return ret_val;
}
void ADC_write_new(){
    volatile uint8_t *ext_mem = (uint8_t *) ADC_start;
    ext_mem[0] = 0x00; 

}
void ADC_read_testing( uint8_t* array)
{
    ADC_write_new();
    volatile char *ext_mem = (char *) ADC_start;
    //_delay_ms((9*NUM_CHANNELS_ADC*2)/F_CPU);
    _delay_ms(30);
    for (uint8_t i = 0; i < NUM_CHANNELS_ADC; i++){
        array[i] = ext_mem[0];
    }

}