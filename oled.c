#include "oled.h"
#include "SPI.h"



volatile OLED_POS_HOLDER current_oled_pos;




void oled_init()
{
    write_COMMAND(0xae); //display off
    write_COMMAND(0xa1); //segment remap
    write_COMMAND(0xda); // common pads hardware:alternative
    write_COMMAND(0x12);
    write_COMMAND(0xc8); //common output scan direction:com63~com0
    write_COMMAND(0xa8); //multiplex ratio mode:63
    write_COMMAND(0x3f);
    write_COMMAND(0xd5); //display divide/osc. freq. mode
    write_COMMAND(0x80);
    write_COMMAND(0x81); // contrast control
    write_COMMAND(0x50);
    write_COMMAND(0xd9); // set pre-charge period
    write_COMMAND(0x21);
    write_COMMAND(0x20); // Set Memory Addressing Mode
    write_COMMAND(0x02);
    write_COMMAND(0xdb); // VCOM deselect level mode
    write_COMMAND(0x30);
    write_COMMAND(0xad); // master configuration
    write_COMMAND(0x00);
    write_COMMAND(0xa4); // out follows RAM content
    write_COMMAND(0xa6); // set normal display
    write_COMMAND(0xaf);  // display on

}

void oled_init_2()
{
    write_COMMAND(0xae); //display off
    write_COMMAND(0xa1); //segment remap
    write_COMMAND_1arg(0xda, 0x12); // common pads hardware:alternative
    write_COMMAND(0xc8); //common output scan direction:com63~com0
    write_COMMAND_1arg(0xa8, 0x3f); //multiplex ratio mode:63
    write_COMMAND_1arg(0xd5, 0x80); //display divide/osc. freq. mode
    write_COMMAND_1arg(0x81, 0x50); // contrast control
    write_COMMAND_1arg(0xd9, 0x21); // set pre-charge period
    write_COMMAND_1arg(0x20, 0x02); // Set Memory Addressing Mode
    write_COMMAND_1arg(0xdb, 0x30); // VCOM deselect level mode
    write_COMMAND_1arg(0xad, 0x00); // master configuration
    write_COMMAND(0xa4); // out follows RAM content
    write_COMMAND(0xa6); // set normal display
    write_COMMAND(0xaf);  // display on
}

void oled_clean(){
    for (uint8_t line = 0; line < 8; line++){
        int address = (0xB0 | line);
        write_COMMAND(address);
        write_COMMAND(0x00); 
        write_COMMAND(0x10);
        set_DC(RW_DATA);
        Slave_select(OLED_SS);
        for (uint8_t column = 0; column < 128; column++){
            SPI_write(0x00); // attempt at setting every pixle to black

        }
        Reset_slave_select(OLED_SS);

    }
}

void oled_anti_clean(){
    for (uint8_t line = 0; line < 8; line++){
        int address = (0xB0 | line);
        write_COMMAND(address);
        write_COMMAND(0x00); 
        write_COMMAND(0x10);
        set_DC(RW_DATA);
        Slave_select(OLED_SS);
        for (uint8_t column = 0; column < 128; column++){
            SPI_write(0xFF); // attempt at setting every pixle to white

        }
        Reset_slave_select(OLED_SS);

    }
}

void write_COMMAND(uint8_t command){
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    Reset_slave_select(OLED_SS);
}
void write_COMMAND_1arg(uint8_t command, uint8_t arg1)
{
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    SPI_write(arg1);
    
    Reset_slave_select(OLED_SS);
}
void write_COMMAND_2arg(uint8_t command, uint8_t arg1, uint8_t arg2)
{
    set_DC(RW_COMMAND);
    Slave_select(OLED_SS);

    SPI_write(command);
    SPI_write(arg1);
    SPI_write(arg2);
    Reset_slave_select(OLED_SS);

}


void write_DATA(uint8_t data){
    set_DC(RW_DATA);
    Slave_select(OLED_SS);
    
    SPI_write(data);
    Reset_slave_select(OLED_SS);

}


void set_addressing_mode(ADDRESSING_MODES mode){ //This is probobly not functional, can be fixed if we actually need to change the mode later
    if (mode == HORIZONTAL)
    {
        write_COMMAND_1arg(0x20,00);
    }
    else if( mode == VERTICAL)
    {
        write_COMMAND(0x20);
        write_COMMAND(01);
    }
    else if( mode == PAGE)
    {
        write_COMMAND(0x20);
        write_COMMAND(10);
    }
    else
    {
        write_COMMAND(0x20);
        write_COMMAND(11);
    }
}

void oled_goto_line(uint8_t line)
{
    if ( (line < 8)){ //Guard to prevent out of bounds
        current_oled_pos.line = line;
        write_COMMAND(0xB0 | line);
    }

}
void oled_goto_column(uint8_t column)
{
    if ( (column < 128)) // Guard to ensure there is no issue with the bouderies

    {
        current_oled_pos.column = column;
        int start = column % 16;
        int end = column / 16;
        write_COMMAND(0x00 | start);
        write_COMMAND(0x10 | end);

        //write_COMMAND()
    }

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
    oled_goto_line(line);
    

}

//void oled_print(char*)
