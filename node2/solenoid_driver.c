#include "solenoid_driver.h"
#include "sam.h"


void solenoid_init(){

    //legg inn riktig pin og port

    PMC-> PMC_PCER0 |= (1 << ID_PIOA);  //enable clk for port C
    PIOA->PIO_PER = PIO_PER_P22;  //overstyr til io
    PIOA->PIO_OER = PIO_OER_P22; //enable output
    
    PIOA->PIO_SODR = PIO_SODR_P22; //set høy
    //PIOA->PIO_CODR = PIO_CODR_P22; //sett lav
   

}
int solenoid_activate(int place_holder_value)
{

    //set riktig pinn etterpå
    if (place_holder_value){

        PIOA->PIO_CODR = PIO_CODR_P22; //sett lav


        for (int i = 0; i < (500000); i++) //delay, adjust to get the correct length pulse //10000000 Whith This value the circuit catches on fire, this value works: 550000
            {}


        PIOA->PIO_SODR = PIO_SODR_P22; //set høy

        return 1;

    }

    return 0;

}


