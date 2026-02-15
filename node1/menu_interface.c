#include "menu_interface.h"

#include "oled.h"
#include "SPI.h"




int menu_index_list[10] = {0,1,2,3,4,5,6,7,8,9};
char* menu_list[10] = {"Meny 1", "Meny 2", "Meny 3", "Meny 4", "Meny 5", "Meny 6","Meny 7","Meny 8","Meny 9","Meny 10"};
//flags to handle JS input correctly
uint8_t handling_JS_dir_output_flag = 0; 
uint8_t handling_JS_button_output_flag = 0; 

void increment_menu()
{
    char* first_menu_item = menu_list[0];
    int first_menu_index = menu_index_list[0];
    for (int index = 1; index < 10; index++ ){
        menu_list[index-1] = menu_list[index];
        menu_index_list[index-1] = menu_index_list[index];
    }
    menu_list[9] = first_menu_item;
    menu_index_list[9] = first_menu_index;
    oled_anti_clean();
}
void decrement_menu()
{
    char* last_menu_item = menu_list[9];
    int last_menu_index = menu_index_list[9];
    for (int index = 8; index >= 0; index-- ){
        menu_list[index+1] = menu_list[index];
        menu_index_list[index+1] = menu_index_list[index];
    }
    menu_list[0] = last_menu_item;
    menu_index_list[0] = last_menu_index;
    oled_anti_clean();
}

void handle_JS_directinal_input(IO_BOARD IO_board_obj){

    JOYSTICK_DIRECTION dir = get_JS_DIR(IO_board_obj);
    //test_function_JS(dir);

    if (dir == UP){
        increment_menu(menu_list);
        _delay_ms(1000);
    }
    else if( dir == DOWN){
       decrement_menu(menu_list); 
       _delay_ms(1000);
    }
}
int handle_JS_button_input(){
    if (JS_button_pressed()){
     return menu_index_list[4];
    }
    else{
        return 40;
    }
}

//main menufunction
void render_main_menu(IO_BOARD IO_board_obj){
    handle_JS_directinal_input(IO_board_obj);
    int a = handle_JS_button_input();
    a = a + 1;
    printf("Menu item index : %i \n\r", a );

    for (int i = 0; i < 8; i++ ){
        if(i == 4)
        {
            render_picked_menu_item(menu_list[i]);

        }
        else
        {
            render_other_menu_items(menu_list[i], i);
        }
    }
}




void render_picked_menu_item(char* menu_item)
{
    oled_change_font_size(FONT_SIZE_LARGE);
    oled_write_string(menu_item, 4, 30);
}
void render_other_menu_items(char* menu_item, uint8_t line)
{
    oled_change_font_size(FONT_SIZE_NORMAL);
    oled_write_string(menu_item, line, 30);
}

void render_picked_menu_item_op_2(char* menu_item)
{
    //change_font_size(FONT_SIZE_NORMAL);
    //oled_write(menu_item, 4, 30)
}
void render_other_menu_items_op2(char* menu_item, uint8_t line)
{
    //change_font_size(FONT_SIZE_NORMAL);
    //oled_scroll_font(menu_item, line)
}

void test_main_menu(){

    while(1){
    IO_BOARD testobject = read_analog_values_dir_IO();
    IO_BOARD testobject2 = convert_position_percent(testobject);
    render_main_menu(testobject2);
    }
}


//sub_menues
void render_sub_menu_1();
void render_sub_menu_2();
void render_sub_menu_3();
void render_sub_menu_4();

