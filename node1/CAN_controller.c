#include "CAN_controller.h"
#include <avr/io.h>
#include <util/delay.h>

#include "SPI.h"

//#define F_CPU 16000000UL //Clock frequency at 16 MHz

void CAN_init(uint8_t mode){

    SPI_init();
    CAN_controller_reset();

    CAN_controller_change_mode(MODE_CONFIG);

    //Bit timing

    CAN_controller_write(MCP_CNF1, 0b11000011); 
    CAN_controller_write(MCP_CNF2, 0b10101010); 
    CAN_controller_write(MCP_CNF3, 0b00000101); 

    //CAN_controller_write(MCP_CNF1, 0b11000000); //SJW length is 3 TQ, BRP = 0
    //CAN_controller_write(MCP_CNF2, 0b10101010); //PROSEG = 2, PRSEG1 = 5, Blt mode = 1
    //CAN_controller_write(MCP_CNF3, 0b00000101); //PRSEG2 = 5





    //CAN_controller_write(MCP_CNF1, 0b00000000); //SJW length is 1 TQ, maybe this is BRP 1, check later
    //CAN_controller_write(MCP_CNF2, 0b10010001); //PROSEG = 2TQ, SP1 = 3TQ, Blt mode = 1
    //CAN_controller_write(MCP_CNF3, 0b00000001); //SP2 = 2TQ

    //Filtes and masks

    //CAN_controller_write(MCP_RXB0CTRL,0b01100000); // recieve all messaages?


    CAN_controller_change_mode(mode);
}

void CAN_transmit(CAN_MESSAGE_FRAME* message){

    //From data sheet: At a minimum, the TXBnSIDH, TXBnSIDL and TXBnDLC registers must be loaded.If data bytes are present in the message, the TXBnDm registers must also be loaded

    CAN_controller_write(MCP_TXB0SIDH, ((message->ID) >> 3) & 0xFF ); // TXBnSIDH 8 MSB of ID (Shifts 3 to the right)
    CAN_controller_write(MCP_TXB0SIDL, ((message->ID & 0x07) << 5 ));     //TXBnSIDL 3 LSB of ID
    CAN_controller_write(MCP_TXB0DLC, message->length);     //TXBnDLC, length?
    
    

    for (int adress_offset = 0; adress_offset < message->length; adress_offset++){

        CAN_controller_write(MCP_TXB0D0 + adress_offset, message->data[adress_offset]);  
    }

    CAN_controller_request_to_send(MCP_RTS_TX0); //sets TXREQ


    uint8_t reg = CAN_controller_read(MCP_TXB0CTRL);


}


uint8_t CAN_recieve(CAN_MESSAGE_FRAME* message){

    //CANINTF.RX0IF, MCP_RX0IF	
    //CANINTF.RX1IF, MCP_MERRF
    //MCP_CANINTF,

    //reset values 
    message->ID = 0;
    message->length = 0;

    for (int8_t i = 0; i < 8; i++){
        message->data[i] = 0;
    }

    uint8_t is_ready_0IF = CAN_controller_read(MCP_CANINTF) & MCP_RX0IF;
    uint8_t is_ready_1IF = CAN_controller_read(MCP_CANINTF) & MCP_RX1IF;

    if (is_ready_0IF){
        uint8_t SIDH = CAN_controller_read(MCP_RXB0SIDH);
        uint8_t SIDL = CAN_controller_read(MCP_RXB0SIDL);
        message->ID = (SIDH << 3) | (SIDL >> 5);

        message->length = CAN_controller_read(MCP_RXB0DLC) & 0x0F;


        for (int adress_offset = 0; adress_offset < message->length; adress_offset++)
        {

           message->data[adress_offset] =  CAN_controller_read(MCP_RXB0D0 + adress_offset);  


        }
        CAN_controller_bit_modify(MCP_CANINTF,0,3); //Resets RX0IF to prevent message from beeing read twice
        
        return 1;

    }
    else if (is_ready_1IF){
        
        uint8_t SIDH = CAN_controller_read(MCP_RXB0SIDH);
        uint8_t SIDL = CAN_controller_read(MCP_RXB0SIDL);
        message->ID = (SIDH << 3) | (SIDL >> 5);

  
        message->length = CAN_controller_read(MCP_RXB1DLC);


        for (int adress_offset = 0; adress_offset < message->length; adress_offset++)
        {
            
           message->data[adress_offset] =  CAN_controller_read(MCP_RXB1D0 + adress_offset);  

        }

        CAN_controller_bit_modify(MCP_CANINTF,0,3); //Resets RX0IF to prevent message from beeing read twice
        return 1;
    }
    return 0;
}
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

void CAN_controller_request_to_send(uint8_t address)
{
    Slave_select(MCP2515_SS);

    SPI_write(address);

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

    _delay_ms(10);

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


    if ((state  & mode) != mode )
    {
    printf("An error occured when setting the mode %i \n\r",mode);
    }
    else
    {
    printf("Mode  %i Success \n\r",mode);
    }


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



void test_CAN_transmitt_and_recieve()
{
    CAN_MESSAGE_FRAME message_1_send;
    CAN_MESSAGE_FRAME message_1_recieve;
    
    message_1_send.length = 8;
    message_1_send.ID = 0x100;
    for (int i = 0; i < message_1_send.length; i++){
        message_1_send.data[i] = i;

    }

    while(1){


    CAN_transmit( &message_1_send);
    _delay_ms(100);
    CAN_recieve(&message_1_recieve);



    uint8_t ID = (message_1_recieve.ID == message_1_send.ID);
    uint8_t length = (message_1_recieve.length == message_1_send.length);
    uint8_t data = 1;

    for (int i = 0; i  < message_1_recieve.length; i++)
    {
        if (message_1_recieve.data[i] != message_1_send.data[i])
        {
            data = 0;
        }
    }
    print_message_object(&message_1_send, &message_1_recieve);


    _delay_ms(4000);  
    }
}

void test_CAN_transmitt_and_recieve_2()
{
    CAN_MESSAGE_FRAME message_1;
    CAN_MESSAGE_FRAME message_2;
    CAN_MESSAGE_FRAME message_3;
    
    CAN_MESSAGE_FRAME message_1_res;
    CAN_MESSAGE_FRAME message_2_res;
    CAN_MESSAGE_FRAME message_3_res;

    message_1.length = 8;
    message_2.length = 8;
    message_3.length = 8;

    message_1.ID = 0x100;
    message_2.ID = 0x200;
    message_3.ID = 0x300;


    for (int i = 0; i < message_1.length; i++){
        message_1.data[i] = i;

    }
    for (int i = 0; i < message_1.length; i++){
        message_2.data[i] = i+1;
        
    }
    for (int i = 0; i < message_1.length; i++){
        message_3.data[i] = i+2;
        
    }

    while(1){
    
    CAN_transmit( &message_1);
    _delay_ms(100);
    CAN_recieve(&message_1_res);
    uint8_t var = CAN_controller_read(MCP_TXB0CTRL) & (1 << 3);



    _delay_ms(100);
    print_message_object(&message_1, &message_1_res);


    CAN_transmit( &message_2);
    _delay_ms(100);
    CAN_recieve(&message_2_res);

    _delay_ms(100);

    print_message_object(&message_2,&message_2_res);

    CAN_transmit( &message_3);
    _delay_ms(100);
    CAN_recieve(&message_3_res);

    _delay_ms(100);

    print_message_object(&message_3, &message_3_res);


    uint8_t ID_1 = (message_1.ID == message_1_res.ID);
    uint8_t length_1 = (message_1.length == message_1_res.length);
    uint8_t data_1 = 1;

    uint8_t ID_2 = (message_2.ID == message_2_res.ID);
    uint8_t length_2 = (message_2.length == message_2_res.length);
    uint8_t data_2 = 1;

    uint8_t ID_3 = (message_3.ID == message_3_res.ID);
    uint8_t length_3 = (message_3.length == message_3_res.length);
    uint8_t data_3 = 1;


    for (int i = 0; i  < message_1.length; i++)
    {
        if (message_1.data[i] != message_1_res.data[i])
        {
            data_1 = 0;
        }
        if (message_2.data[i] != message_2_res.data[i])
        {
            data_2 = 0;
        }
        if (message_3.data[i] != message_3_res.data[i])
        {
            data_3 = 0;
        }
    }

    uint8_t first_correct = (ID_1 && length_1 && data_1);
    uint8_t second_correct = (ID_2 && length_2 && data_2);
    uint8_t third_correct = (ID_3 && length_3 && data_3);



    _delay_ms(4000);  
    }

}

void print_message_object(CAN_MESSAGE_FRAME* message_1, CAN_MESSAGE_FRAME* message_2)
{
    printf("ID: sendt: %i, recieved: %i \n\r", message_1->ID, message_2->ID);
    printf("Length: sendt %i, recieved: %i \n\r", message_1->length, message_2->length);
    for (int i = 0; i < message_1->length; i++){
            printf("Data element %i: sendt: %i, recieved: %i \n\r", i, message_1->data[i], message_2->data[i]);

    }

}

void print_message_object_1(CAN_MESSAGE_FRAME* message)

{
    printf("ID:%i \n\r", message->ID);
    printf("Length: %i\n\r", message->length);
    for (int i = 0; i < message->length; i++){
            printf("Data element %i: %i \n\r", i, message->data[i]);

    }

}



void test_CAN_transmitt_to_node_2(){


    CAN_MESSAGE_FRAME message_1;
    CAN_MESSAGE_FRAME message_2;
    CAN_MESSAGE_FRAME message_3;
    
    CAN_MESSAGE_FRAME message_1_res;
    CAN_MESSAGE_FRAME message_2_res;
    CAN_MESSAGE_FRAME message_3_res;

    message_1.length = 8;
    message_2.length = 8;
    message_3.length = 8;

    message_1.ID = 0x100;
    message_2.ID = 0x200;
    message_3.ID = 0x300;


    for (int i = 0; i < message_1.length; i++){
        message_1.data[i] = i;

    }
    for (int i = 0; i < message_1.length; i++){
        message_2.data[i] = i+1;
        
    }
    for (int i = 0; i < message_1.length; i++){
        message_3.data[i] = i+2;
        
    }

    while(1){
    
    CAN_transmit( &message_1);
    print_message_object_1( &message_1);
    _delay_ms(100);


    uint8_t var = CAN_controller_read(MCP_TXB0CTRL) & (1 << 3);

    //while (CAN_controller_read(MCP_TXB0CTRL) & (1 << 3)){
    //    printf("TEXREQ not clear");
    //};

    CAN_transmit( &message_2);
    print_message_object_1( &message_2);
    _delay_ms(100);



    CAN_transmit( &message_3);
    print_message_object_1( &message_3);

    _delay_ms(4);  
    }

}

void test_CAN_transmitt_to_node_3(){


    CAN_MESSAGE_FRAME message_1;

    
    CAN_MESSAGE_FRAME message_1_res;



    message_1.length = 8;


    message_1.ID = 0x001;

    int count = 0;

    for (int i = 0; i < message_1.length; i++){

        if (count == 0){

            message_1.data[i] = 0;
            count = 1;
        }
        else{
            message_1.data[i] = 1;
            count = 0;

        }
        

    }


    while(1){
    
    CAN_transmit( &message_1);
    print_message_object_1( &message_1);
    _delay_ms(100);


    uint8_t var = CAN_controller_read(MCP_TXB0CTRL) & (1 << 3);

    //while (CAN_controller_read(MCP_TXB0CTRL) & (1 << 3)){
    //    printf("TEXREQ not clear");
    //};

    _delay_ms(100);  
    }

}





