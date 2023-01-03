#ifndef HD44780_PCF8574_H_
#define HD44780_PCF8574_H_

#include <avr/pgmspace.h> //PSTR

#define LOW 0
#define HIGH 1

#define A0 LOW
#define A1 LOW
#define A2 LOW

#define PCF8574_ADDR		(0x20 | (A2 << 2) | (A1 << 1) | (A0 << 0))
#define PCF8574A_ADDR	(0x38 | (A2 << 2) | (A1 << 1) | (A0 << 0))

#define PCF8574_ADDRESS (PCF8574A_ADDR<<1)

#define RS_BIT_POS		0
#define E_BIT_POS		1
#define D4_BIT_POS		2
#define D5_BIT_POS		3
#define D6_BIT_POS		4
#define D7_BIT_POS		5

//#define LED_BIT_POS		6		//You can use two additional output from register Q6 & Q7 as another GPIO outputs, for controlling LED, BUZZER etc.
//#define BUZZER_BIT_POS	7

#define HIGH 1
#define LOW 0


/* RS */
#define RS_HIGH		send_to_expander( 1<<RS_BIT_POS, HIGH)
#define RS_LOW		send_to_expander( 1<<RS_BIT_POS, LOW)


/* RW */  //CONNECT TO GND
//#define RW_HIGH	send_to_expander( 1<<RW_BIT_POS, HIGH)
//#define RW_LOW	send_to_expander( 1<<RW_BIT_POS, HIGH)


/* E */
#define E_HIGH		send_to_expander( 1<<E_BIT_POS, HIGH)
#define E_LOW		send_to_expander( 1<<E_BIT_POS, LOW)


/* D4...D7*/
#define D4_HIGH		send_to_expander( 1<<D4_BIT_POS, HIGH)
#define D4_LOW		send_to_expander( 1<<D4_BIT_POS, LOW)

#define D5_HIGH		send_to_expander( 1<<D5_BIT_POS, HIGH)
#define D5_LOW		send_to_expander( 1<<D5_BIT_POS, LOW)

#define D6_HIGH		send_to_expander( 1<<D6_BIT_POS, HIGH)
#define D6_LOW		send_to_expander( 1<<D6_BIT_POS, LOW)

#define D7_HIGH		send_to_expander( 1<<D7_BIT_POS, HIGH)
#define D7_LOW		send_to_expander( 1<<D7_BIT_POS, LOW)

//#define LED_ENABLE		send_to_expander( 1<<LED_BIT_POS, HIGH)
//#define LED_DISABLE		send_to_expander( 1<<LED_BIT_POS, LOW)

//#define BUZZER_ENABLE		send_to_expander( 1<<BUZZER_BIT_POS, HIGH)
//#define BUZZER_DISABLE	send_to_expander( 1<<BUZZER_BIT_POS, LOW)


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


void send_to_expander(uint8_t data, uint8_t set_or_reset);
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
