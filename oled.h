#ifndef OLED_H
#define OLED_H


#include <avr/io.h>
#include <stdio.h>

#include <stdint.h>

 

typedef struct {
    int line;
    int column;
} OLED_POS_HOLDER;

typedef enum {
    HORIZONTAL,
    VERTICAL,
    PAGE,
    INVALID

} ADDRESSING_MODES;

//define write commands
void write_COMMAND(uint8_t command);
void write_COMMAND_1arg(uint8_t command, uint8_t arg1);
void write_COMMAND_2arg(uint8_t command, uint8_t arg1, uint8_t arg2);


void write_DATA(uint8_t data);



void oled_init();
void oled_init_2();
void oled_clean(); //this might cover reset?
void oled_anti_clean();


void set_addressing_mode(ADDRESSING_MODES mode);

void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_pos(uint8_t row, uint8_t column);

void oled_reset();
void oled_home();

void oled_clear_line(uint8_t line);

void oled_print(char*);

#endif