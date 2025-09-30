#ifndef OLED_H
#define OLED_H


#include <avr/io.h>
#include <stdio.h>

#include <stdint.h>

 

typedef struct {
    int line;
    int colum;
} OLED_POS_HOLDER;

typedef enum {
    HORIZONTAL,
    VERTICAL,
    PAGE,
    INVALID

} ADDRESSING_MODES;

//define write commands
void writeCOMMAND(uint8_t command);
void writeCOMMAND_SERIES(uint8_t command, uint)
void write_DATA();


void oled_init();

void set_addressing_mode(ADDRESSING_MODES mode);

void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_pos(uint8_t row, uint8_t column);

void oled_reset();
void oled_home();

void oled_clear_line(uint8_t line);

void oled_print(char*);

#endif