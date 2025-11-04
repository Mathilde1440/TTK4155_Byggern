#include "pwm_driver.h"
#include "sam.h"


#define MCK 84000000
//#define PWM_CLOCK (MCK/8) // we have choosen Timer_Clock2, defined in table 36-1 as MCK/8
#define PWM_SERVO_PERIOD 20000u  
#define PWM_D_PREF 1500u
#define PWM_D_MIN 900u
#define PWM_D_MAX 2100u

void timer_counter_init()
{

    //PMC->PMC_WPMR |= ( 0x504D43) |~PMC_WPMR_WPEN; // skru av write protection, may have to be at the start of the function
    

    //PMC-> PMC_PCER1 |= PMC_PCDR1_PID36; // enable clock for PWM (PID = Pheriferal identifiers s. 39 datasheet) Might be incorrect
    PMC-> PMC_PCER1 |= (1 << (ID_PWM - 32)); // This might be the same as the line above, test both

    PMC-> PMC_PCER0 |= (1 << ID_PIOB); // enable clock fpr IO port B



    PIOB->PIO_PDR = PIO_PDR_P13; // Disable I/O pheriferal for IO port B13
    PIOB->PIO_ABSR |= PIO_ABSR_P13; // Choose Pheriferal B for IO port B (signal PWMH1)
   

    PWM->PWM_WPCR = (0x50574D << 8) | (0b111111 << 2) | (0 << 0); // disable WP on all related PWM registers


    // We chose the clock to be 1 MHz, simply beacuse it makes the rest of the calculations easier.
    PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); //devide mastreclock by 84 to obtain a clock of 1 Mhz. (Prescaler = 1 for MCK)



    REG_PWM_CMR1 = 0b1011; //0b1011; // found this registerdefinition in "instance_pwm.h " in sam. Sets clock to CLK A. PWM_CMR_CPRE_CLKA
    REG_PWM_CPRD1 = PWM_SERVO_PERIOD; //sets period to 20 ms
    REG_PWM_CDTY1 = PWM_SERVO_PERIOD-PWM_D_PREF; //set duty cyckle et 1.5 ms (center position), as decribed as prefered in the task (register description at s. 1046 in the datasheet) // Verdien er trukket fra MCK for å invertere duty-cyle 



    PWM->PWM_ENA = (1 << 1); // enable channel 1

    PIOB->PIO_OER = PIO_OER_P13; //enable output

}

uint32_t clamp_signal(uint32_t signal,uint32_t lower_bounds, uint32_t uppper_bounds){

    if ((signal > lower_bounds) && (signal < uppper_bounds))
    {

    return signal;

    }

    else if ( signal <= lower_bounds) 
    {

        return lower_bounds;
    }

    else
    {
        return uppper_bounds;
    }

}

void calulate_and_set_DC(int8_t direction_PRC){

    for (int i = 0; i < 10000; i++) // works as a slight delay 
    {}

    uint32_t DC = -6* direction_PRC + 1500;
    printf("DC clac : %i \n\r", DC);
    set_DC(DC);
}

void set_DC(uint32_t duty_cycle){

    uint32_t clamped_dc = clamp_signal(duty_cycle, PWM_D_MIN, PWM_D_MAX);
    printf("DC clamp : %i \n\r", clamped_dc);
    REG_PWM_CDTY1 = PWM_SERVO_PERIOD - duty_cycle;

}