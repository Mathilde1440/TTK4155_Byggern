

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include "labdag1.h"
#include "labdag2.h"




#define BAUD 9600UL
#define MYUBRR ((F_CPU / (16UL * BAUD)) - 1) 



int main(void) {
    
    

    USART_Init(MYUBRR);

    //while (1){
    
        //test_med_echo();
     
        //printf("ing");  //printf

        //test_for_latch();
    //}

    SRAM_init();
    SRAM_test();

    //test_for_decoder();
    
}
