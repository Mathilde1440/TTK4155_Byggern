#include "adc.h"
#include "sam.h"

#define ADC_TRESH 1200//place-holde value, need to scope the adc

int count_flag = 0; //prevents point dupication when the ball is in the goal zone




void adc_init()
{
   
    ADC->ADC_MR = ADC_MR_FREERUN_ON; //Sets adc to free run mode, i.e not witing for hardware triges, sets startuptime to 8 periods of ADCclock
    PMC-> PMC_PCER1 |= (1 << (ID_ADC - 32)); //enable clock for adc
    //(1 << (ID_ADC - 32));//PMC_PCER1_PID37


    //use channel 0 , input pin -> AD0 = I/O line PA2

    //ADC register overview : 
    //MR : s. 1334
    //CHER : s.1339
    //CR: s.1332
    //CDR[x]: s. 1351
    //LCDR: s. 1341

  

    ADC->ADC_CHER = ADC_CHER_CH0; // enable channel 0


    ADC->ADC_CR = ADC_CR_START; //starts adc conversion


}


uint16_t adc_read(){
    uint16_t data = ADC->ADC_CDR[0];
    return data; // returns entire data register for channel 1
}






uint16_t keep_score(uint16_t old_score)
{
    uint16_t adc_value = adc_read();

    if ((adc_value < ADC_TRESH) && !count_flag)  // Equals logic low and a goal is scored
    {
        count_flag = 1;
        return old_score + 1;
    }

    else{ //logic high, no goal scored

        if((adc_value > ADC_TRESH) && count_flag) //restes the flag when the ball is out of the goal zone -> no dupication
        {
            count_flag = 0; 
        }

        return old_score;
    }
}

void test_adc_read(){

    while (1){

        uint16_t adc_value = adc_read();
        printf("Current ADC value: %i \n\r", adc_value);
    }

}
void test_keep_score()
{
    uint16_t score = 0;

    while (1)
    {
        uint16_t adc_value = adc_read();
        score = keep_score(score);
        printf("Current score is: %i \n\r", score);
    }
    

}


