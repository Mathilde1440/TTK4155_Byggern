#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "joystick.h"


//util functions
void increment_menu();
void decrement_menu();

//function for user input
void handle_JS_directinal_input(IO_BOARD IO_board_obj);
int handle_JS_button_input();
void render_picked_menu_item();
void render_other_menu_items(char* menu_item, uint8_t line);

//rendering functions
void render_picked_menu_item_op_2();
void render_other_menu_items_op_2();

//test functions

//main menufunction
void render_main_menu(IO_BOARD IO_board_obj);

//sub_menues
void render_sub_menu_1();
void render_sub_menu_2();
void render_sub_menu_3();
void render_sub_menu_4();

void test_main_menu();

#endif