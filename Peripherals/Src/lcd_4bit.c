/*
 * lcd_4bit.c
 *
 *  Created on: Oct 23, 2023
 *      Author: dell
 */

/*
 * GPIO set up
 */

#include "lcd_4bit.h"


void LCD_config_gpio()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    // Khởi tạo chân GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LCD_RS | LCD_E;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;
    HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(LCD_PORT, LCD_RS | LCD_E, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7, GPIO_PIN_RESET);
}
void LCD_Write(uint8_t Data, uint8_t Mode)
{
	uint8_t Data_H = Data >> 4;
	uint8_t Data_L = Data;
	if (Mode == cmd_reg)
	{
		HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET); // RS = 0, write cmd
	}
	else if (Mode == data_reg)
	{
		HAL_GPIO_WritePin(LCD_PORT, LCD_RS,GPIO_PIN_SET); // RS = 1, write data
	}
	HAL_GPIO_WritePin(GPIOB, LCD_D4, Data_H & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D5, Data_H >> 1 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D6, Data_H >> 2 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D7, Data_H >> 3 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_RESET);
	HAL_Delay(1);

	HAL_GPIO_WritePin(GPIOB, LCD_D4, Data_L & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D5, Data_L >> 1 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D6, Data_L >> 2 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_D7, Data_L >> 3 & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT, LCD_E, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void LCD_Init()
{

	HAL_Delay(150);
	LCD_Write(0x33, cmd_reg);
	HAL_Delay(50);
	LCD_Write(0x33, cmd_reg);
	HAL_Delay(50);
	LCD_Write(0x32, cmd_reg);
	HAL_Delay(50);

	LCD_Write(LCD_FUNCTIONSET, cmd_reg);
	LCD_Write(LCD_CLEARDISPLAY, cmd_reg);
	HAL_Delay(2);
	LCD_Write(LCD_DISPLAYONOFF, cmd_reg);
	LCD_Write(LCD_ENTRYMODESET, cmd_reg);

	LCD_Write(LCD_CLEARDISPLAY, cmd_reg);
	HAL_Delay(2);
	LCD_Write(LCD_RETURNHOME, cmd_reg);
}

void SetCursor(uint8_t Xpos, uint8_t Ypos)
{
	uint8_t DRAM_ADDRESS = 0x00;
	uint8_t DRAM_OFFSET[4] = {0x00, 0x40, 0x14, 0x54};
	if (Xpos >= 16)
	{
		Xpos = 16 - 1;
	}
	if (Ypos >= 2)
	{
		Ypos = 2;
	}
	DRAM_ADDRESS = DRAM_OFFSET[Ypos] + Xpos;
	LCD_Write(LCD_SETDDRAMADDR | DRAM_ADDRESS, cmd_reg);
}
void WriteChar(char character)
{
	LCD_Write(character, data_reg);
}
void WriteString(char *String)
{
	while (*String)
	{
		WriteChar(*String++);
		//		HAL_Delay(100);
	}
}
void Clear()
{
	LCD_Write(LCD_CLEARDISPLAY, cmd_reg);
	HAL_Delay(5);
}
void ReturnHome()
{
	LCD_Write(LCD_RETURNHOME, cmd_reg);
	HAL_Delay(5);
}

void CursorOn()
{
	LCD_Write(0x0E, cmd_reg); // màn hình on, con trỏ on
}
void CursorOff()
{

	LCD_Write(LCD_DISPLAYONOFF, cmd_reg); // màn hình on,con trỏ off
}
void BlinkOn()
{

	LCD_Write(0x0F, cmd_reg);
}
void BlinkOff()
{
	LCD_Write(LCD_DISPLAYONOFF, cmd_reg);
}

