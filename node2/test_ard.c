#include "test_ard.h"

void test_ard(){
    PIOB->PIO_WPMR &= ~PIO_WPMR_WPEN;
    PMC->PMC_WPMR &= ~PMC_WPMR_WPEN;

    PMC-> PMC_PCER0 = PMC_PCER0_PID12;

    

    PIOB->PIO_PER = PIO_PER_P13;  //overstyr til io
    PIOB->PIO_OER = PIO_OER_P13; //enable output

    PIOB->PIO_PUDR  = PIO_PUDR_P13; //ingen pull-up

    PIOB->PIO_CODR = PIO_CODR_P13; //sett lav
    //PIOB->PIO_SODR = (1u << 13); //set høy
}