/*
 * lcd_4bit.h
 *
 *  Created on: Oct 23, 2023
 *      Author: dell
 */

#ifndef INC_LCD_4BIT_H_
#define INC_LCD_4BIT_H_

#include "main.h"
#define LCD_PORT GPIOA
#define LCD_RS GPIO_PIN_8
#define LCD_E GPIO_PIN_9

#define LCD_D4 GPIO_PIN_0
#define LCD_D5 GPIO_PIN_1
#define LCD_D6 GPIO_PIN_10
#define LCD_D7 GPIO_PIN_11


#define cmd_reg 0
#define data_reg 1
// constant

// commands
#define LCD_CLEARDISPLAY 0x01 // xóa màn hình
#define LCD_RETURNHOME 0x02	  // Trở về vị trí đầu dòng

#define LCD_ENTRYMODESET 0x06	// Dịch con trỏ sang phải khi ghi/đọc data
#define LCD_DISPLAYCONTROL 0x08 // Tắt màn hình tắt con trỏ
#define LCD_CURSORSHIFT 0x10	// Dịch con trỏ sang trái không làm thay đổi nội dung DDRAM
#define LCD_FUNCTIONSET 0x28	// Đặt chức năng giao tiếp 4 bit cao, 2 dòng, 5x8dots
#define LCD_SETPOINTER1 0x40	// Chuyển con trỏ về đầu dòng 1
#define LCD_SETPOINTER2 0xC0	// Chuyển con trỏ về đầu dòng 2
#define LCD_DISPLAYONOFF 0x0C	// Màn hình ON, xóa con trỏ

#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

void LCD_config_gpio();
void LCD_Init();
void SetCursor(uint8_t Xpos, uint8_t YPos);
void WriteChar(char character);
void WriteString(char *String);
void Clear();
void ReturnHome();
void CursorOn();
void CursorOff();
void BlinkOn();
void BlinkOff();

#endif /* INC_LCD_4BIT_H_ */
