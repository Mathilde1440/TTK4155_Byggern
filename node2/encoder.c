#include "encoder.h"
#include "sam.h"


void encoder_init()
{
    PMC-> PMC_PCER0 |= (1 << ID_PIOC);  //enable clk for port C
    PMC-> PMC_PCER1 |= (1 << (ID_TC6 - 32)); //enable clock TC2
 

    REG_TC2_CCR0 = TC_CCR_CLKEN; //enable clock 2

    PIOC->PIO_PDR = PIO_PER_P25;  //disable io
    //PIOC->PIO_OER = PIO_OER_P25; //enable output
    PIOC->PIO_ABSR |= PIO_ABSR_P25; // Choose Pheriferal B for IO port 

    PIOC->PIO_PDR = PIO_PER_P26;  //disable io
    //PIOA->PIO_OER = PIO_OER_P26; //enable output
    PIOC->PIO_ABSR |= PIO_ABSR_P26; // Choose Pheriferal B for IO port 



    REG_TC2_BMR |= TC_BMR_POSEN | TC_BMR_QDEN; // enable postion meassurments and QDEC enable 
    REG_TC2_CMR0 = TC_CMR_TCCLKS_XC0; //clock select s871
    REG_TC2_CCR0 = TC_CCR_SWTRG; // resets and starts the clock
}

int32_t read_encoder_pos()
{
    return REG_TC2_CV0; 
}