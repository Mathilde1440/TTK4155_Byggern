#include "CAN_controller.h"
#include <avr/io.h>
#include <util/delay.h>

#include "SPI.h"

//#define F_CPU 16000000UL //Clock frequency at 16 MHz



uint8_t CAN_controller_read(uint8_t address)
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_READ);
    SPI_write(address);

    uint8_t data = SPI_read();

    Reset_slave_select(MCP2515_SS);
    return data;
}

void CAN_controller_write(uint8_t address,uint8_t data)
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_WRITE);
    SPI_write(address);
    SPI_write(data);

    Reset_slave_select(MCP2515_SS);
}

void CAN_controller_request_to_send()
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_RTS_TX0);

    Reset_slave_select(MCP2515_SS);
} 

void CAN_controller_bit_modify(uint8_t address, uint8_t data, uint8_t mask)
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_BITMOD);
    SPI_write(address);
    SPI_write(mask);
    SPI_write(data);

    Reset_slave_select(MCP2515_SS);

}

void CAN_controller_reset()
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_RESET);

    Reset_slave_select(MCP2515_SS);

}

uint8_t CAN_controller_read_status()
{
    Slave_select(MCP2515_SS);

    SPI_write(MCP_READ_STATUS);
    uint8_t status = SPI_read();

    Reset_slave_select(MCP2515_SS);
    return status;
}

void CAN_controller_change_mode(uint8_t mode)
{
    CAN_controller_write(MCP_CANCTRL,mode);
    uint8_t state = CAN_controller_read(MCP_CANSTAT);
    
//    if ((state  & mode) != mode ){
//       printf("An error occured when setting the mode \n\r");
//   }
//    else
//    {
//       printf("Mode Success \n\r");
//    }

}


void CAN_controller_init(){
    CAN_controller_reset();
    _delay_ms(10);
    uint8_t state = CAN_controller_read(MCP_CANSTAT);






    CAN_controller_change_mode(MODE_LOOPBACK);
}








void slave_select_test_CAN_2()
{
    while(1){
        Slave_select(MCP2515_SS);
        _delay_ms(10000);
        Reset_slave_select(MCP2515_SS);
        _delay_ms(10000);  
    }
}

//TEST RTS

void test_RTS(){
    uint8_t control_value = CAN_controller_read(MCP_TXB0CTRL);
    uint8_t control_negative = (( control_value & (1 << 3 )));
    if (control_negative == 0 ){
        printf("RTS correct init value \n\r");
    }
    else{
        printf("RTS incorrect init value \n\r");
    }

    uint8_t value = CAN_controller_read(MCP_TXB0CTRL);


    uint8_t control = (( value & (1 << 3 )));
    if (control != 0 ){
        printf("RTS test success\n\r");
    }
    else{
        printf("RTS test is failed\n\r");

    }


}


void test_bit_modify(){
    uint8_t befor_test = CAN_controller_read(MCP_CANCTRL);
    uint8_t init_value = (( befor_test & (1 << 1 )));
    if (init_value == 0 ){
        printf("Init value = %i \n\r", 0);
    }
    else{
        printf("Init value = %i \n\r", 1);
    }

    CAN_controller_bit_modify(MCP_CANCTRL, 1,1);

    uint8_t after_test_1 = CAN_controller_read(MCP_CANCTRL);
    uint8_t value_after_1 = (( after_test_1 & (1 << 1 )));
    if (value_after_1 == 0 ){
        printf("Value after 1. test = %i \n\r", 0);
    }
    else{
        printf("Value after 1. test  = %i \n\r", 1);
    }

    CAN_controller_bit_modify(MCP_CANCTRL, 0,1);

    uint8_t after_test_2 = CAN_controller_read(MCP_CANCTRL);
    uint8_t value_after_2 = (( after_test_2& (1 << 1 )));
    if (value_after_2 == 0 ){
        printf("Value after 2. test = %i \n\r", 0);
    }
    else{
        printf("Value after 2. test  = %i \n\r", 1);
    }
}

//test read status

void test_read_status(){
    uint8_t status = CAN_controller_read_status();
    uint8_t befor = (( status & (1 << 2 )));

    CAN_controller_request_to_send();

    uint8_t staus2 = CAN_controller_read_status();
    uint8_t after = (( status & (1 << 2 )));

    printf("Value befor test: %i, value after test %i \r\n",befor,after);


}
void test_can_controller_reset(){

    CAN_controller_change_mode(MODE_LOOPBACK);
     uint8_t state = CAN_controller_read(MCP_CANSTAT);

   if ((state  & MODE_MASK) != MODE_LOOPBACK){
       printf("An error occured when setting the mode \n\r");
   }
   else
   {
     printf("Mode Success \n\r");
    }
    

    CAN_controller_reset();
    uint8_t state2 = CAN_controller_read(MCP_CANSTAT);
    if ((state2  & MODE_MASK) != MODE_CONFIG){
    printf("An error occured during init \n\r");
  }
   else
   {
      printf("Success init \n\r");
    }
}





