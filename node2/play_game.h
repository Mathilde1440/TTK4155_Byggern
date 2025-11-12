#ifndef PLAY_GAME_H_
#define PLAY_GAME_H_


#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>


#include "can_controller.h"

#include "io_board_driver_node_2.h"




//recive function for CAN, only alter obj
void transmitt_lives(); 


void recieve_IO_Board_obj(IO_BOARD* obj_1, IO_BOARD* obj_2); //add a variable to IO_BOARD which tells if the object has been alterd this run. 
void process_IO_BOARD_obj(IO_BOARD* obj_1, IO_BOARD* obj_2);

//motor and encoder functions



void run_servo(IO_BOARD* obj_1, IO_BOARD* obj_2);
void run_motor(IO_BOARD* obj_1, IO_BOARD* obj_2); //run PI controller and set speed;

void rund_motor_board(IO_BOARD* obj_1, IO_BOARD* obj_2); //runs the three functions above




//shoot the ball function
void shoot_ball(IO_BOARD* obj_1, IO_BOARD* obj_2);

//score_functions

void keep_game_score();
void print_game_score();

void set_game_over();


//game_over_function?

void set_game_over();

//handle mailboxes


//main_game_loop
void play_game();


#endif