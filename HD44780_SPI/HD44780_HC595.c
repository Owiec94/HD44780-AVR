#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "HD44780_HC595.h"

void send_to_register(uint8_t data, uint8_t set_or_reset)
{
	static uint8_t register_data = 0;
	if(1 == set_or_reset)
	{
		register_data |= data;
	}
	else
	{
		register_data &= ~data;
	}
	
	STCP_LOW;
	for(uint8_t i = 0; i < 8; i++)
	{
		SHCP_LOW;
		
		DS_LOW;
		if(register_data & (1<< (7-i) ) )
		{
			DS_HIGH;
		}
		SHCP_HIGH;
	}
	STCP_HIGH;
}

static void register_set_all_low(void)			//disable all output on startup
{
	STCP_LOW;
	DS_LOW;
	for(uint8_t i = 0; i < 8; i++)
	{
		SHCP_LOW;
		
		SHCP_HIGH;
	}
	STCP_HIGH;
}

static void lcd_write(uint8_t v, uint8_t rs)
{
	if(LCD_DATA == rs)
	{
		RS_HIGH;
	}
	else
	{
		RS_LOW;
	}
	
	E_HIGH;

    if(v & 0x10) D4_HIGH; else D4_LOW;
    if(v & 0x20) D5_HIGH; else D5_LOW;
    if(v & 0x40) D6_HIGH; else D6_LOW;
    if(v & 0x80) D7_HIGH; else D7_LOW;
	
    E_LOW;  
	_delay_us(1000);								//it really depends of performance of Your LCD
	
	E_HIGH;
	
    if(v & 0x01) D4_HIGH; else D4_LOW;
    if(v & 0x02) D5_HIGH; else D5_LOW;
    if(v & 0x04) D6_HIGH; else D6_LOW;
    if(v & 0x08) D7_HIGH; else D7_LOW;
	
    E_LOW;
	_delay_us(1000);								//as above
	
}

static void lcd_send_4bits(uint8_t v)
{
	E_HIGH;
	if(v & 0x01) D4_HIGH; else D4_LOW;
	if(v & 0x02) D5_HIGH; else D5_LOW;
	if(v & 0x04) D6_HIGH; else D6_LOW;
	if(v & 0x08) D7_HIGH; else D7_LOW;
	E_LOW;
}

void lcd_init(void)
{
	DS_DDR |= (1<<DS_PIN);
	STCP_DDR |= (1<<STCP_PIN);
	SHCP_DDR |= (1<<SHCP_PIN);
	
	register_set_all_low();
	
#ifdef STARTUP_DELAY
	_delay_ms(750);								//value really depends of quality of Your LCD
#endif

	for(uint8_t i = 0; i < 3; i++)
	{
		lcd_send_4bits( (LCD_FUNCTION_ADDR | LCD_FUNCTION_8BIT_MODE) >> 4 );
		_delay_ms(5);
	}
	
	lcd_send_4bits(LCD_FUNCTION_ADDR >> 4);
	_delay_ms(5);
	
	LCD_FUNCTION(LCD_FUNCTION_4BIT_MODE | LCD_FUNCTION_2LINE | LCD_FUNCTION_5x8DOTS);
	LCD_DISPLAY(LCD_DISPLAY_OFF);
	lcd_clear();
	LCD_DISPLAY(LCD_DISPLAY_ON | LCD_DISPLAY_CURSOR_BLINK_OFF | LCD_DISPLAY_CURSOR_OFF);	
}

void lcd_save_to_cgram(uint8_t addr, uint8_t pixels[])
{
	if(addr < 8)
	{
		lcd_write(LCD_CG_RAM_SET_ADDR | (addr << 3), LCD_COMMAND);
		for(uint8_t i = 0; i < 8; i++)
		{
			lcd_write(pixels[i], LCD_DATA);
		}
	}
	lcd_cursor_home();
}

void lcd_clear(void)
{
	lcd_write(LCD_CLEAR_ADDR, LCD_COMMAND);
	_delay_ms(2);
}

void lcd_cursor_home(void)
{
	lcd_write(LCD_CURSOR_HOME_ADDR, LCD_COMMAND);
	_delay_ms(2);
}

void lcd_pos(uint8_t x, uint8_t y)
{
	lcd_write(LCD_DD_RAM_SET_ADDR | (x + ( y * 0x40) ), LCD_COMMAND);
}

void lcd_print_RAM(char *str)
{
    while(*str)
	{
        lcd_write(*str++, LCD_DATA);
	}
}

void lcd_print_FLASH(const char *str)
{
	uint8_t data = 0;
	while( (data = pgm_read_byte(str++)) )
	{
		lcd_write(data, LCD_DATA);
	}
}

void lcd_print_char(unsigned char c)
{
	lcd_write(c, LCD_DATA);
}

void lcd_print_cgram(uint8_t addr)
{
	if(addr < 8)
	{
		lcd_write(addr, LCD_DATA);
	}
}

//use itoa instead of sprintf, since its lighter and faster for AVR
void lcd_uint8(uint8_t val, uint8_t system)
{
	char buffer[9];								//in case if binary (system==2) 8bit + NULL
	itoa(val, buffer, system);
	lcd_print_RAM(buffer);
}

void lcd_int8(int8_t val, uint8_t system)
{
	char buffer[9];
	itoa(val, buffer, system);
	lcd_print_RAM(buffer);
}

void lcd_uint16(uint16_t val, uint8_t system)
{
	char buffer[17];								//in case if binary (system==2) 16it + NULL
	itoa(val, buffer, system);
	lcd_print_RAM(buffer);
}

void lcd_int16(int16_t val, uint8_t system)
{
	char buffer[17];
	itoa(val, buffer, system);
	lcd_print_RAM(buffer);
}


