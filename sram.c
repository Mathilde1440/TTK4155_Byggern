#include "sram.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void SRAM_init(){
    //MCUCSR |= (1<<JTD);
    MCUCR |= (1 << SRE);
    //SFIOR |= (1<<XMM2);
    SFIOR = 0b100;
}

void SRAM_test(void)
{
    volatile uint8_t *ext_ram = (uint8_t *)0x1800;
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");

    uint16_t seed = rand();
    
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = (uint8_t)rand();
        ext_ram[i] = some_value;
        uint8_t retrieved_value = ext_ram[i];
        if (retrieved_value != some_value) {
            printf("Write phase error: ext_ram[%4u] = %02X (should be %02X)\n",
                   i, retrieved_value, some_value);
            write_errors++;
        }
    }
    
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = (uint8_t)rand();
        uint8_t retrieved_value = ext_ram[i];
        if (retrieved_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4u] = %02X (should be %02X)\n",
                   i, retrieved_value, some_value);
            retrieval_errors++;
        }
    }
    

    printf("SRAM test completed with\n%4u errors in write phase and\n%4u errors in retrieval phase\n\n",
           write_errors, retrieval_errors);
}
