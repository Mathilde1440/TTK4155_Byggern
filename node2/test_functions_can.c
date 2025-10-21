#include "test_functions_can.h"

void print_message_object_node_2(CAN_MESSAGE* message)

{
    printf("ID:%i \n\r", message->id);
    printf("Length: %i\n\r", message->data_length);
    for (int i = 0; i < message->data_length; i++){
            printf("Data element %i: %i \n\r", i, message->data[i]);

    }

}

void test_rec_node_1(){

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;


    while (1)
    {
        printf("%i \n\r", (can_receive( &message_1, 0) == 0) );

        if (can_receive( &message_1, CAN_SR_MB) == 0) 
        {
            print_message_object_node_2( &message_1);
        }

        if (can_receive( &message_2, 2) == 0)
        {
            print_message_object_node_2( &message_2);
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}

}