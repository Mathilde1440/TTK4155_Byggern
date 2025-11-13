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
        
        //delay transmisson when the ADC is converting, time found in the data sheet s.17(https://learn-eu-central-1-prod-fleet01-xythos.content.blackboardcdn.com/5def77a38a2f7/5686089?X-Blackboard-S3-Bucket=learn-eu-central-1-prod-fleet01-xythos&X-Blackboard-Expiration=1763067600000&X-Blackboard-Signature=74efDrRAn%2FE%2BzmW%2BhY4OUaahYlfBLPTxEE%2BxV%2FUBY4s%3D&X-Blackboard-Client-Id=303508&X-Blackboard-S3-Region=eu-central-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27ADC%2520MAX156CNG%252B%25281%2529.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEIr%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaDGV1LWNlbnRyYWwtMSJIMEYCIQCSHTDhVdF2mi2xP8fPR4VcMQHWjyQdCCu4MsX8pFoD0wIhAJ88dqkvWFB8CXQaujOftbPhiaU10BTPU5nZz4RGwiTFKr4FCFMQBBoMNjM1NTY3OTI0MTgzIgwSw6%2FqSE9SyrkRgTQqmwXJCUkeJ1kWmJWnCT26Ip%2BXkLe2WfSE4O6hLM9nDoN1ZAsMoi09eGTijRG1hGgY9iKJfKnnRF1G%2Fed9OXWOIPu9%2FDbLwHXhdPrXTDCmMMwLofZvpqAotcc1G74u4%2BdzacdMmYhTBG9vTJS1LFIGXuSsI3nff4STvIAjku7t1rTXmDb8Vm8NRJzRgb9kb2gYpY8UYQR4oJLjdXVF1GKaohop3IvOkP5Wd5dGVPjR%2B%2B%2Bm6i8SqnK7rFGv1ziR3ODojEgfbwCwd000GsdLl222Rogw%2BF9VR9O2p7BHgMi6C1j8v2dIflYa9kQpiDpdfXnfHCh5z1lB9vRnhEzdbz070Zj582IiMkwrZsDMq1TRDTsK8dcxOxR0FGwDgzDawzGcwM133VEgT1v6dXz0NORMioQTOhxMbn5lX1%2FzZjsZVZJKb2Vp%2FKStnoSLmZW8JCQ%2FinXcbp%2BORBM6BFB58C8654X5oLWkuZrGFAUONEFVlAqB%2Bpxzv1Gm%2FPE1Zc32m0bVfrdSyUuidh3MAqRa7WWmHsOuwEjz2oEQtNqgiWUDrK0Zjc%2F99VzIdmWfW6n2VFx7oc8ogpXS0fMneH%2BYDuunG2rXBeubHWQtvGJ%2FUD7Bp8J6ilKNoIQjU5r%2Bq0Xl37jngjybUOoLGzl3jVMA9X0h7swZzanEcEM5J9T9mYip%2BLeiR3yrwWdFFEZ0FLIom11s9Ub1HkqqSpbmlU%2BqDy319HDcvxXksd9%2BGOx%2BXs2ctZAHtHD6b%2Bdcnu1jfXB4jdFhxf1yLHcN3PA5K1yTBfB8ragCvFdkQUNgjDBIBvdHFu5JtD0vNYVCluzdd1dQOlHDpivnal0iBV0Od20i3H%2BRgLJybJVf3jJb8niIixk%2Fz9gfzWn%2BIr89AsvdOVsjMJat2MgGOrABOYb1DzBoydQyBnabO77mOAahctpT8o7kQ1MvpB0fWBR8haIj0FOeIiLAMsscBjArWwW7%2BUIXp5NZxKlco%2BH50QL7vw5DvvX8iMbhrOVhCUjUcKz5Crk2%2FM%2B%2F9l4TMr2qIWObdMrFo067uVWUMqggKy3vPUP17BjAD1ZCHDNO2B5DrkqVHMZhLj6Bdvo2W1cuM7iBw2ubXj%2B%2BZM%2Fjzl%2BMFiKJLDS69WHp7AZdjoyIOZg%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20251113T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLZIRXPIF3%2F20251113%2Feu-central-1%2Fs3%2Faws4_request&X-Amz-Signature=00e1da46ea4f7ed530e784aa30d4e17d380d459dec1890e8155398b4dee8d600)
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