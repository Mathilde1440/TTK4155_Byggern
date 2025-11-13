#include "gameplay.h"

#include <util/delay.h>

#include "oled.h"
#include "SPI.h"

#include <avr/pgmspace.h>


#include "adc.h"
#include "uart.h"
#include "sram.h"

#include "labdag1.h"
#include "labdag2.h"




int game_menu_index_list[10] = {0,1,2,3,4,5,6,7,8,9};
char* game_menu_list[10] = {"Restart game", "Meny 2", "Meny 3", "Meny 4", "Meny 5", "Meny 6","Meny 7","Meny 8","Meny 9","Meny 10"};
//flags to handle JS input correctly
uint8_t game_handling_JS_dir_output_flag = 0; 
uint8_t game_handling_JS_button_output_flag = 0; 


void game_transmitt_IO_BOARD_obj(IO_BOARD* obj){

    CAN_MESSAGE_FRAME msg;

    encode_JS_direction(obj, &msg);

    obj->JS_button_pressed = JS_button_pressed();
    CAN_transmit(&msg); 

}

int recieve_lives()
{

    CAN_MESSAGE_FRAME msg_1;

    int sucsess = CAN_recieve(&msg_1);

    if (!sucsess){
        printf("Faied to recieve message \n\r");
    }

    int lives = msg_1.data[0];

    return lives;

}


void game_increment_menu()
{
    char* first_menu_item = game_menu_list[0];
    int first_menu_index = game_menu_index_list[0];
    for (int index = 1; index < 10; index++ ){
        game_menu_list[index-1] = game_menu_list[index];
        game_menu_index_list[index-1] = game_menu_index_list[index];
    }
    game_menu_list[9] = first_menu_item;
    game_menu_index_list[9] = first_menu_index;
    oled_anti_clean();
}
void game_decrement_menu()
{
    char* last_menu_item = game_menu_list[9];
    int last_menu_index = game_menu_index_list[9];
    for (int index = 8; index >= 0; index-- ){
       game_menu_list[index+1] = game_menu_list[index];
        game_menu_index_list[index+1] = game_menu_index_list[index];
    }
    game_menu_list[0] = last_menu_item;
    game_menu_index_list[0] = last_menu_index;
    oled_anti_clean();
}

void game_handle_JS_directinal_input(IO_BOARD IO_board_obj)
{

    JOYSTICK_DIRECTION dir = get_JS_DIR(IO_board_obj);
    //test_function_JS(dir);

    if (dir == UP){
        game_increment_menu(game_menu_list);
        _delay_ms(1000);
    }
    else if( dir == DOWN){
       game_decrement_menu(game_menu_list); 
       _delay_ms(1000);
    }
}

int game_handle_JS_button_input()
{
    if (JS_button_pressed()){
     return game_menu_index_list[4];
    }
    else{
        return 40;
    }
}
void game_render_main_menu(IO_BOARD IO_board_obj)
{
    game_handle_JS_directinal_input(IO_board_obj);
    int a = game_handle_JS_button_input();
    a = a + 1;
    printf("Menu item index : %i \n\r", a );

    for (int i = 0; i < 8; i++ ){
        if(i == 4)
        {
            game_render_picked_menu_item(game_menu_list[i]);

        }
        else
        {
            game_render_other_menu_items(game_menu_list[i], i);
        }
    }
}


void game_render_picked_menu_item(char* menu_item)
{
    oled_change_font_size(FONT_SIZE_LARGE);
    oled_write_string(menu_item, 4, 30);
}

void game_render_other_menu_items(char* menu_item, uint8_t line)
{
    oled_change_font_size(FONT_SIZE_NORMAL);
    oled_write_string(menu_item, line, 30);
}

void run_menu(){


    IO_BOARD testobject = read_analog_values_dir_IO();
    IO_BOARD testobject2 = convert_position_percent(testobject);
    game_render_main_menu(testobject2);

}




void oled_render_lives(int lives){


    switch (lives)
    {
    case 0:
        /* code */
        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Game over", 4, 30);


        oled_change_font_size(FONT_SIZE_SMALL);

        oled_write_string("Trykk tre ganger for å se meny", 5, 30);


        break;
    case 1:

        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Du har 1 liv igjen", 4, 30);

        break;
    case 2:
        
        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Du har 2 liv igjen", 4, 30);

        break;
    case 3:

        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Du har 3 liv igjen", 4, 30);

        break;
    case 4:

        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Du har 4 liv igjen", 4, 30);
        
        break;
    case 5:
        
        oled_change_font_size(FONT_SIZE_LARGE);
        oled_write_string("Du har 5 liv igjen", 4, 30);


        break;
    
    default:
        break;
    }
}


void game_loop(){


}


