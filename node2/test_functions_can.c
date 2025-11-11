#include "test_functions_can.h"
#include "can_controller.h"
#include "sam.h"

#include "pwm_driver.h"
#include "motor_driver.h"
#include "PI_controller.h"
#include "encoder.h"
#include "solenoid_driver.h"

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
            //test_function_JS(dir);
            //printf("X: %i, Y: %i, Button: %i", obj_1.X_JS, obj_1.Y_JS, obj_1.JS_Button_pressed);

            if (obj_1.JS_Button_pressed)
            {
                printf("Button is pressed \n\r");
            }



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, &obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_2);
            //test_function_JS(dir);
            if (obj_1.JS_Button_pressed)
            {
                printf("Button is pressed \n\r");
            }
            
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
            
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, &obj_1);
            convert_position_percent(&obj_1);

           
            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_1);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_1.X_JS_PRC);



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
          
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, &obj_2);
            convert_position_percent(&obj_2);
           

            JOYSTICK_DIRECTION dir = get_JS_DIR(&obj_2);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_2.X_JS_PRC);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}
}


void recieve_io_obj(IO_BOARD* obj_1, IO_BOARD* obj_2){

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;


    while (1)
    
    {

        if (can_receive( &message_1, 1) == 0) 
        {
            //printf("triggerd 1 \n\r");
            //print_message_object_node_2( &message_1);
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, obj_1);
            convert_position_percent(obj_1);

            //print_IO_BOARD_obj(&obj_1);
            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_1);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_1->Y_JS_PRC);
            set_direction_and_speed(obj_1);



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, obj_2);
            convert_position_percent(obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_2);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_2->Y_JS_PRC);
            set_direction_and_speed(obj_2);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}
}

void test_PI_controller(IO_BOARD* obj_1, IO_BOARD* obj_2){

    int button_flag;

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;

    PI_CONT dir_obj_1;
    PI_CONT dir_obj_2;

    double K_p = 0.6;
    double K_i = 0.2;


    while (1)
    
    {

        if (can_receive( &message_1, 1) == 0) 
        {
            //printf("triggerd 1 \n\r");
            //print_message_object_node_2( &message_1);
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, obj_1);
            convert_position_percent(obj_1);

            //print_IO_BOARD_obj(&obj_1);
            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_1);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_1->Y_JS_PRC);

            uint32_t encoder_position = read_encoder_pos();

            //printf("JS_PRC_outside %i \n\r", obj_1->X_JS_PRC);

            double p_ref = calc_p_ref_lin(*obj_1);
            //printf("P_ref outisde: %f \n \r", p_ref);

            double dc= PI_controller(K_p, K_i, p_ref, encoder_position, &dir_obj_1);

            set_speed_and_direction_2(abs(dc*100),dir_obj_1.dir);

            if(obj_1->JS_Button_pressed)
            {
                button_flag =1;
            }

            int rest = solenoid_activate(button_flag);
            button_flag = 0;
            

            


            //set_direction_and_speed(obj_1);



          
            
            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR;
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, obj_2);
            convert_position_percent(obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_2);
            //test_function_JS(dir);


            calulate_and_set_DC(obj_2->Y_JS_PRC);
            //set_direction_and_speed(obj_2);

            uint32_t encoder_position = read_encoder_pos();

            double p_ref = calc_p_ref_lin(*obj_2);

            double dc= PI_controller(K_p, K_i, p_ref, encoder_position, &dir_obj_2);

            set_speed_and_direction_2(abs(dc*100), dir_obj_2.dir);
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;

            
        }
          
    }

    for (int i = 0; i < 10000; i++)
    {}
}