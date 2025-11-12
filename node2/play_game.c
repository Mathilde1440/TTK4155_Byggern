#include "play_game.h"

#include "test_functions_can.h"
#include "can_controller.h"
#include "sam.h"

#include "pwm_driver.h"
#include "motor_driver.h"
#include "PI_controller.h"
#include "encoder.h"
#include "solenoid_driver.h"

#include "adc.h"

int button_flag = 0;
int count_lives = 8;

int game_over = 0;

int adc_flag= 0;

// int count_flag = 0; //prevents point dupication when the ball is in the goal zone

#define ADC_TRESH 2000//place-holde value, need to scope the adc

void transmitt_lives(){

   
    CAN_MESSAGE message_1;

    message_1.id = 0x001;
    message_1.data_length = 8;
    message_1.data[0] = count_lives;



    int sucess = can_send(&message_1, 2);
}



void recieve_IO_Board_obj(IO_BOARD* obj_1, IO_BOARD* obj_2){

    CAN_MESSAGE message_1;
    CAN_MESSAGE message_2;


        if (can_receive( &message_1, 1) == 0) 
        {
            //printf("triggerd 1 \n\r");
            //print_message_object_node_2( &message_1);
            transform_CAN_msg_to_IO_BOARD_obj(&message_1, obj_1);
            //print_IO_BOARD_obj(&obj_1);
            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_1);
            //test_function_JS(dir);
            //printf("X: %i, Y: %i, Button: %i", obj_1.X_JS, obj_1.Y_JS, obj_1.JS_Button_pressed);

            if (obj_1->JS_Button_pressed)
            {
                //printf("Button is pressed \n\r");
            }



            CAN0->CAN_MB[1].CAN_MCR = CAN_MCR_MTCR; //clears mailbox, is not cleared automatically, might be beacause interrups are disabled
        }

        if (can_receive( &message_2, 2) == 0)
        {
            //printf("triggerd 2 \n\r");
            //print_message_object_node_2( &message_2);
            transform_CAN_msg_to_IO_BOARD_obj(&message_2, obj_2);
            //print_IO_BOARD_obj(&obj_2);

            JOYSTICK_DIRECTION dir = get_JS_DIR(obj_2);
            //test_function_JS(dir);
            if (obj_2->JS_Button_pressed)
            {
                //printf("Button is pressed \n\r");
            }
            
            CAN0->CAN_MB[2].CAN_MCR = CAN_MCR_MTCR;
        }
          


    for (int i = 0; i < 10000; i++)
    {}

}


void process_IO_BOARD_obj(IO_BOARD* obj_1, IO_BOARD* obj_2){
    convert_position_percent(obj_1);
    convert_position_percent(obj_2);

}


void run_servo(IO_BOARD* obj_1, IO_BOARD* obj_2)
{

    calulate_and_set_DC(obj_1->Y_JS_PRC);

}
void run_motor(IO_BOARD* obj_1, IO_BOARD* obj_2){


    PI_CONT dir_obj_1;

    //PI_CONT dir_obj_2;

    double K_p = 2.5;
    double K_i = 0.6;

    uint32_t encoder_position = read_encoder_pos();

    double p_ref = calc_p_ref_lin(*obj_1);


    for (int i = 0; i < 100000; i++) //delay needed for proper control
    {}
    

    double dc= PI_controller(K_p, K_i, p_ref, encoder_position, &dir_obj_1);


    set_speed_and_direction_2(abs(dc*100),dir_obj_1.dir);
}

void rund_motor_board(IO_BOARD* obj_1, IO_BOARD* obj_2){

    run_servo(obj_1,obj_2);
    run_motor(obj_1,obj_2);

}
void shoot_ball(IO_BOARD* obj_1, IO_BOARD* obj_2){
        if(obj_1->JS_Button_pressed)
    {
        button_flag = 1;
    }

    int rest = solenoid_activate(button_flag);
    button_flag = 0;
}


void keep_game_score(){


    uint16_t adc_value = adc_read();


    if ((adc_value < ADC_TRESH) && !adc_flag)  // Equals logic low and a goal is scored
    {
        adc_flag = 1;
        count_lives--;
    }

    else
    { //logic high, no goal scored

        if((adc_value > ADC_TRESH) && adc_flag) //restes the flag when the ball is out of the goal zone -> no dupication
        {
            adc_flag = 0; 
        }
    }


}

void print_game_score(){

   

    if( !game_over)
    {
        printf("You currently have %i lives left \n\r", count_lives);

    }

    else 
    {
        printf("Game over \n\r");

    }

}

void set_game_over()
{

    if (count_lives <= 0)
    {
        game_over = 1;
    }


}


void play_game(){



    while(1){
       


    IO_BOARD obj_1;
    IO_BOARD obj_2;


    recieve_IO_Board_obj(&obj_1, &obj_2);
    process_IO_BOARD_obj(&obj_1, &obj_2);


    rund_motor_board(&obj_1, &obj_2);


    shoot_ball(&obj_1, &obj_2);

    keep_game_score();
    print_game_score();

    set_game_over();



    }
    

}

