#include "pwm_driver.h"
#include "sam.h"

void timer_counter_init()
{
    

    PMC-> PMC_PCER1 |= PMC_PCDR1_PID36; // turn on clock for PWM (PID = Pheriferal identifiers s. 39 datasheet)

    PMC->PMC_WPMR &= ~PMC_WPMR_WPEN; // skru av write protection, may have to be at the start of the function
    



}