#ifndef HD44780_H_
#define HD44780_H_

#include <avr/pgmspace.h> //PSTR

#define EN_DDR 	DDRD
#define RS_DDR 	DDRD

#define EN_PORT PORTD
#define RS_PORT PORTD

#define EN_PIN 	PD6
#define RS_PIN 	PD5

#define D4_DDR 	DDRC
#define D5_DDR 	DDRC
#define D6_DDR 	DDRC
#define D7_DDR 	DDRC

#define D4_PORT PORTC
#define D5_PORT PORTC
#define D6_PORT PORTC
#define D7_PORT PORTC

#define D4_PIN 	PC0
#define D5_PIN 	PC1
#define D6_PIN 	PC2
#define D7_PIN 	PC3


/* RS */
#define RS_HIGH		RS_PORT|=(1<<RS_PIN)
#define RS_LOW		RS_PORT&=~(1<<RS_PIN)


/* RW */  //CONNECT TO GND
//#define RW_HIGH		RW_PORT|=(1<<RW_PIN)
//#define RW_LOW		RW_PORT&=~(1<<RW_PIN)


/* E */
#define E_HIGH		EN_PORT|=(1<<EN_PIN)
#define E_LOW		EN_PORT&=~(1<<EN_PIN)


/* D4...D7*/
#define D4_HIGH		D4_PORT|=(1<<D4_PIN)
#define D4_LOW		D4_PORT&=~(1<<D4_PIN)

#define D5_HIGH		D5_PORT|=(1<<D5_PIN)
#define D5_LOW		D5_PORT&=~(1<<D5_PIN)

#define D6_HIGH		D6_PORT|=(1<<D6_PIN)
#define D6_LOW		D6_PORT&=~(1<<D6_PIN)

#define D7_HIGH		D7_PORT|=(1<<D7_PIN)
#define D7_LOW		D7_PORT&=~(1<<D7_PIN)


#define LCD_COMMAND	0
#define LCD_DATA	1


#define LCD_CLEAR_ADDR					0x01

#define LCD_CURSOR_HOME_ADDR			0x02


#define LCD_ENTRY_MODE_ADDR				0x04	//LCD ENTRY MODE SET RS=0 R/W=0 data= 000001IS

#define LCD_ENTRY_MODE_INCREMENT		0x01
#define LCD_ENTRY_MODE_DECREMENT		0x00
#define LCD_ENTRY_MODE_RIGHT			0x02
#define LCD_ENTRY_MODE_LEFT				0x00
#define LCD_ENTRY_MODE(SI)				lcd_write(LCD_ENTRY_MODE_ADDR | SI , LCD_COMMAND)


#define LCD_DISPLAY_ADDR				0x08	//LCD DISPLAY RS=0 R/W=0 data= 00001DCB

#define LCD_DISPLAY_ON					0x04
#define LCD_DISPLAY_OFF					0x00
#define LCD_DISPLAY_CURSOR_ON			0x02
#define LCD_DISPLAY_CURSOR_OFF			0x00
#define LCD_DISPLAY_CURSOR_BLINK_ON		0x01
#define LCD_DISPLAY_CURSOR_BLINK_OFF	0x00
#define LCD_DISPLAY(DCB)				lcd_write(LCD_DISPLAY_ADDR | DCB, LCD_COMMAND)


#define LCD_CURSOR_SHIFT_ADDR			0x10	//LCD DISPLAY CURSOR SHIFT RS=0 R/W=0 data= 0001CDxx

#define LCD_CURSOR_DISPLAY_MOVE			0x08
#define LCD_CURSOR_CURSOR_MOVE			0x00
#define LCD_CURSOR_MOVE_RIGHT			0x04
#define LCD_CURSOR_MOVE_LEFT			0x00
#define LCD_CURSOR_SHIFT(SR)			lcd_write(LCD_CURSOR_SHIFT_ADDR | SR, LCD_COMMAND)


#define LCD_FUNCTION_ADDR				0x20	//LCD FUNCTION SET RS=0 R/W=0 data= 001DNFxx

#define LCD_FUNCTION_8BIT_MODE			0x10
#define LCD_FUNCTION_4BIT_MODE			0x00
#define LCD_FUNCTION_2LINE				0x08
#define LCD_FUNCTION_1LINE				0x00
#define LCD_FUNCTION_5x10DOTS			0x04
#define LCD_FUNCTION_5x8DOTS			0x00
#define LCD_FUNCTION(DNF)				lcd_write(LCD_FUNCTION_ADDR | DNF, LCD_COMMAND);

#define LCD_CG_RAM_SET_ADDR				0x40
#define LCD_DD_RAM_SET_ADDR				0x80

#define STARTUP_DELAY					//need for stabilise voltage after startup

void lcd_init(void);
void lcd_save_to_cgram(uint8_t addr, uint8_t pixels[]);
void lcd_clear(void);
void lcd_cursor_home(void);
void lcd_pos(uint8_t x, uint8_t y);
void lcd_print_RAM(char *str);
void lcd_print_FLASH(const char *str);
void lcd_print_char(unsigned char c);
void lcd_print_cgram(uint8_t addr);
void lcd_uint8(uint8_t val, uint8_t system);
void lcd_int8(int8_t val, uint8_t system);
void lcd_uint16(uint16_t val, uint8_t system);
void lcd_int16(int16_t val, uint8_t system);

#define lcd_print(str) lcd_print_FLASH(PSTR(str))

#endif
