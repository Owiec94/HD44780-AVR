# HD44780
This repo contain library for HD44780 standard GPIO, PCF8574(I2C) and 74HC595 (software SPI) version

## HD44780 standard GPIO
Classic library for control 6 GPIOs (RS,E,D4..D7) from MCU. If You want reduce number of used GPIO use one of below solution:

## HD44780 I2C
Library for control LCD by I2C protocol based on PCF8574/PCF8574A expander, using only 2 pins (SDA & SCL), remember to pull-up these wires to VCC through resistors. In header select which chip You prefer to use and it's A0..A2 pins represents three least significant address bits connected to VCC/GND. You can still drive P6 and P7 outputs for other application (ie. LED, buzzer etc.)

## HD44780 SPI
Library for control LCD by using 74HC595 based on software SPI. This solution uses only 3 pins but the most advantage is You can use any GPIO port which is helpful for remap if You create Your own PCB. You can still drive Q6 and Q7 outputs for other application (ie. LED, buzzer etc.) and also Q7n for connect next shift register.
