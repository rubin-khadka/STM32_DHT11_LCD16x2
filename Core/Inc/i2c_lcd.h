/*
 * i2c_lcd.h
 *
 *  Created on: Feb 19, 2026
 *      Author: Rubin Khadka
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "main.h"

// Function Prototype
void lcd_init (void);   // Initialize lcd
void lcd_send_cmd (char cmd);  // Send command to the lcd
void lcd_send_data (char data);  // Send data to the lcd
void lcd_send_string (char *str);  // Send string to the lcd
void lcd_put_cur(int row, int col);  // Put cursor at the entered position row, col;
void lcd_clear (void);
void lcd_complete_test(void);

#endif /* INC_I2C_LCD_H_ */
