#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <avr/io.h>
#include "joystick.h"

#include <stdio.h>

#include <stdint.h>


void game_transmitt_IO_BOARD_obj(IO_BOARD* obj);
int recieve_lives();

void game_increment_menu();
void game_decrement_menu();


void game_handle_JS_directinal_input(IO_BOARD IO_board_obj);
int game_handle_JS_button_input();

void game_render_main_menu(IO_BOARD IO_board_obj);

void game_render_picked_menu_item(char* menu_item);
void game_render_other_menu_items(char* menu_item, uint8_t line);

void run_menu();

void back_to_menue(IO_BOARD* obj, int lives);

int return_reset_request();


void oled_render_lives(int lives);

void game_loop();



#endif