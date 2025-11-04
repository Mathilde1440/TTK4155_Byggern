#include "test_functions_can.h"
#include "can_controller.h"
#include "sam.h"
#include "io_board_driver_node_2.h"
#include "pwm_driver.h"

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

        if (can_receive( &message_1, 1) == 0) 
        {
            printf("triggerd 1 \n\r");
            print_message_object_node_2( &message_1);
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            printf("triggerd 2 \n\r");
            print_message_object_node_2( &message_2);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}

}


void test_JS_driver(){

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;

    IO_BOARD obj_1;
    IO_BOARD obj_2;


    while (1)
    
    {

        if (can_receive( &message_1, 1) == 0) 
        {
            //printf("triggerd 1 \n\r");
            //print_message_object_node_2( &message_1);
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, &obj_1);
            //print_IO_BOARD_obj(&obj_1);
            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_1);
            test_function_JS(dir);



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, &obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_2);
            test_function_JS(dir);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}

}

void test_servo_driver(){

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;

    IO_BOARD obj_1;
    IO_BOARD obj_2;


    while (1)
    
    {

        if (can_receive( &message_1, 1) == 0) 
        {
            //printf("triggerd 1 \n\r");
            //print_message_object_node_2( &message_1);
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, &obj_1);
            convert_position_percent(&obj_1);

            //print_IO_BOARD_obj(&obj_1);
            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_1);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_1.X_JS_PRC);



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, &obj_2);
            convert_position_percent(&obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_2);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_2.X_JS_PRC);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}

    




}