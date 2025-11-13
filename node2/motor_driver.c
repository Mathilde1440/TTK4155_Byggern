#include "motor_driver.h"
#include "sam.h"

             // 20 kHz
#define PWM_PERIOD 14000 
#define PWM_D_PREF 1500

void motor_init()
{


    PMC->PMC_PCER1 |= (1u << (ID_PWM - 32));

    PMC-> PMC_PCER0 |= (1 << ID_PIOB); // enable clock fpr IO port B



    PIOB->PIO_PDR = PIO_PDR_P12; // Disable I/O pheriferal for IO port B12
    PIOB->PIO_ABSR |= PIO_ABSR_P12; // Choose Pheriferal B for IO port B (signal PWMH1)
   

    PWM->PWM_WPCR = (0x50574D << 8) | (0b111111 << 2) | (0 << 0); // disable WP on all related PWM registers


    // We chose the clock to be 1 MHz, simply beacuse it makes the rest of the calculations easier.
    PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); //devide mastreclock by 84 to obtain a clock of 1 Mhz. (Prescaler = 1 for MCK)



    REG_PWM_CMR0 = PWM_CMR_CPRE_CLKA; //0b1011; // found this registerdefinition in "instance_pwm.h " in sam. Sets clock to CLK A. PWM_CMR_CPRE_CLKA
    REG_PWM_CPRD0 = PWM_PERIOD; //sets period to 20 ms
    REG_PWM_CDTY0 = PWM_PERIOD-PWM_PERIOD/STILL;//set duty cyckle et 1.5 ms (center position), as decribed as prefered in the task (register description at s. 1046 in the datasheet) // Verdien er trukket fra MCK for å invertere duty-cyle 
    //REG_PWM_CDTYUPD0 = (PWM_PERIOD*)/100u;
    uint32_t c = (PWM_PERIOD * (100-STILL_PRC)) / 100u;
    REG_PWM_CDTYUPD0 = c; 



    PWM->PWM_ENA = (1 << 0); // enable channel 0

    PIOB->PIO_OER = PIO_OER_P12; //enable output



    //configure phase/dir pin for motor
    PMC-> PMC_PCER0 |= (1 << ID_PIOC);  //enable clk for port C
    PIOC->PIO_PER = PIO_PER_P23;  //overstyr til io
    PIOC->PIO_OER = PIO_OER_P23; //enable output
    PIOC->PIO_CODR = PIO_CODR_P23; 
}
void set_speed_and_direction_2(double DC, MOTOR_DIRECTION dir)
{

    int DC_MAX = 100;

    if (dir == M_LEFT){
        set_motor_direction(M_LEFT);
    }
    else{

        set_motor_direction(M_RIGHT);

    }
    double DC_CLAMP = DC;

    if (DC > DC_MAX){

        DC_CLAMP = DC_MAX;

    }
    uint32_t DC_set = (PWM_PERIOD * (100-abs(DC_CLAMP))) / 100u;
    REG_PWM_CDTYUPD0 = DC_set; 

}



void set_direction_and_speed(IO_BOARD* obj){

    MOTOR_SPEED_SCALER scale= STILL;
    int dir_flag = 0;

    JOYSTICK_DIRECTION dir = get_JS_DIR(obj);

    if ( dir != NEUTRAL)
    {
        if ( dir == LEFT)
        {
            //PIOC->PIO_CODR = PIO_CODR_P23; 
            PIOC->PIO_SODR = PIO_SODR_P23;
            dir_flag = 0;
        }
        else if (dir == RIGHT)
        {
            dir_flag = 1;
            PIOC->PIO_CODR = PIO_CODR_P23;

        }
    }


    if ( abs(obj->X_JS_PRC) <= 20 )

    {
        scale= STILL_PRC;

    }

    else if ( abs(obj->X_JS_PRC) < 70)
    {
        scale = MEDIUM_PRC;
    }
    else if ( abs(obj->X_JS_PRC) >= 70)
    {
        scale = FAST_PRC;
    }

    printf("Scale %i, direction flag %i \n\r", scale, dir_flag);



    //EG_PWM_CDTY0 = PWM_PERIOD-PWM_PERIOD/scale;
    uint32_t dc = (PWM_PERIOD * (100-scale)) / 100u;
    REG_PWM_CDTYUPD0 = dc; 

}

void set_motor_direction( MOTOR_DIRECTION dir){

    if (dir == M_LEFT){

        PIOC->PIO_SODR = PIO_SODR_P23;

    }
    else
    {

        PIOC->PIO_CODR = PIO_CODR_P23;
        
    }
}


