#include "oled.h"
#include "SPI.h"



volatile OLED_POS_HOLDER current_olde_pos;




void oled_init()
{
    write_c(0xae); //display off
    write_c(0xa1); //segment remap
    write_c(0xda); // common pads hardware:alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8); //multiplex ratio mode:63
    write_c(0x3f);
    write_c(0xd5); //display divide/osc. freq. mode
    write_c(0x80);
    write_c(0x81); // contrast control
    write_c(0x50);
    write_c(0xd9); // set pre-charge period
    write_c(0x21);
    write_c(0x20); // Set Memory Addressing Mode
    write_c(0x02);
    write_c(0xdb); // VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); // master configuration
    write_c(0x00);
    write_c(0xa4); // out follows RAM content
    write_c(0xa6); // set normal display
    write_c(0xaf);  // display on

}

void writeCOMMAND(uint8_t command){
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    Reset_slave_select(OLED_SS);
}

void writeCOMMAND_1_ARG(uint8_t command, uint){
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    Reset_slave_select(OLED_SS);
}
void writeCOMMAND_2_ARG(uint8_t command, uint){
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    Reset_slave_select(OLED_SS);
}


void write_DATA(uint8_t data){
    set_DC(RW_DATA);
    Slave_select(OLED_SS);
    
    SPI_write(data);
    Reset_slave_select(OLED_SS);

}
void set_addressing_mode(ADDRESSING_MODES mode){
    if (mode == HORIZONTAL)
    {
        writeCOMMAND(00);
    }
    else if( mode == VERTICAL)
    {
        writeCOMMAND(01);
    }
    else if( mode == PAGE)
    {
        writeCOMMAND(10);
    }
    else
    {
        writeCOMMAND(11);
    }
}

void oled_goto_line(uint8_t line)
{
    if ( (line < 127) && (line > 0) ) // Guard to ensure there is no issue with the bouderies

    {
        current_olde_pos(line);
        set_addressing_mode();
    }

}
void oled_goto_column(uint8_t column)
{

}
void oled_pos(uint8_t row, uint8_t column)
{
    oled_goto_line(row);
    oled_goto_column(column);
}

void oled_reset()
{

}
void oled_home()

{  
    oled_pos(0,0);
}

void oled_clear_line(uint8_t line)
{

}

void oled_print(char*)
{

}