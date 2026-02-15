#include "PI_controller.h"
#include "sam.h"
#define ENCODER_MAX 2700
double integral = 0;
int time_flag = 0;
//int clk_count = 0;
double last_u_value = 0;



#define SAMPLE_TIME 0.0105
#define FREQ_CLOCK 84000000/8 //maybe start a timer counter and just poll it
#define DISC_COUNTER  ((uint32_t)(SAMPLE_TIME * (double)FREQ_CLOCK)) // Number ofg "ticks" on TC1 for T to equal 10.5 ms 


#define U_MIN -1000
#define U_MAX 1000
#define U_RANGE 2000



//notat til å lese encoder
// int32_t pos1 = read_encoder_pos();
// delay_us(100); // sample interval
// int32_t pos2 = read_encoder_pos();
// int32_t delta = pos2 - pos1; // counts per 100 µs

//delta > 0 -> motor snurrer "fremover"
//delta < 0 -> motor snurrer bakover


//spørsmål, trengs det en dac for å transfomere outputsuignal til analog verdi?





void counter_init(){

    //TC_CVx -> contains real time counter value (TC Counter Value Register)
    //PMC-> PMC_PCER0 |= (1 << ID_PIOA);  //enable clk for port A
    PMC-> PMC_PCER0 |= (1 << (ID_TC4)); //enable clock TC1

    

    REG_TC1_CMR1 = TC_CMR_TCCLKS_TIMER_CLOCK2 |TC_CMR_WAVE |TC_CMR_WAVSEL_UP_RC; //change value to timer_CLOCK1 (mck/8) in waveform

    REG_TC1_RC1 = DISC_COUNTER;

    REG_TC1_IER1 = 0;
    REG_TC1_IDR1 = 0xFFFFFFFF;

    REG_TC1_CCR1 = TC_CCR_CLKEN | TC_CCR_SWTRG; //enable clock 1, resets and starts the clock

}

void test_counter()
{
    int flag_value = REG_TC1_SR1;

    int counter_value = REG_TC1_CV1; 

    int compare = flag_value & TC_SR_CPCS;

    if ( compare != 0)
    {
        printf("Counter value  %i\n\r", counter_value);
       
        time_flag = 1; //makshit interupt, basically a poll
    }

  
}

double calc_p_ref_lin(IO_BOARD obj)
{
    double p_ref = (27.0/2.0) * obj.X_JS_PRC + 1350;


    //printf("JS_PRC %i \n\r", obj.X_JS_PRC);

    //printf("P_ref befor clamp: %f \n\r", p_ref);

    if (p_ref < 0){
        p_ref = 0;
    }
    if (p_ref > ENCODER_MAX){
        p_ref = ENCODER_MAX;
    }

     //printf("P_ref after clamp: %f \n\r", p_ref);
 
    return p_ref;
}

uint32_t calc_p_ref(IO_BOARD* obj,int encoder_output){
    
    int p = encoder_output;
    int p_ref = p + (ENCODER_MAX * obj->X_JS_PRC)/100;

    if (p_ref < 0){
        p_ref = 0;
    }
    if (p_ref > 2500){
        p_ref = 2500;
    }



    //printf("p_ref = %i \n\r", p_ref);


    return p_ref;

}


double PI_controller(double Kp, double Ki, double p_ref, int encoder_output, PI_CONT* obj){

    //printf("p_ref start of fubction: %f \n\r", p_ref);
        

    int flag_value = REG_TC1_SR1;

    int compare = flag_value & TC_SR_CPCS;
    
   
    if (compare != 0)
    {
       
        time_flag = 1; //makshit interupt, basically a poll
        //REG_TC1_CCR1 = TC_CCR_SWTRG; //reset and start
        
    }

    if (time_flag){

        
        int p = encoder_output;
        int e = p_ref - p;

        if(abs(e) < 10)
        {
            e = 0;
        }

        if (e < 0){
            obj->dir = M_LEFT;
        }

        else if ( e >= 0){
            obj->dir = M_RIGHT;

        }

        //if (e > -10 && e < 10) e = 0;



        integral += e*SAMPLE_TIME;

        
        double prop = Kp * e;
        
        double u = prop + Ki  * integral;


        double u_prc = u/U_MAX;

        if (u_prc >1){

            u_prc = 1;
            
        }

        if (u_prc < -1){

            u_prc = -1;
            
        }

        
        last_u_value = u_prc;
        
        time_flag = 0;  //reset time flag
        //printf("p_ref befor return: %f \n\r", p_ref);
        //printf("Prop: %f, integral: %f \n\r", prop, integral);
        //printf("u = %d, p_ref %i, e = %i \n\r", u,p_ref, e);
        

        return u_prc;

    }

    return last_u_value; 

}



