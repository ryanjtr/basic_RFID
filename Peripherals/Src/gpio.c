/*
 * gpio.c
 *
 *  Created on: Nov 1, 2023
 *      Author: dell
 */
#include "gpio.h"

void gpio_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = REDLED | GREENLED | LOCK | BUZZER;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, REDLED, 0);
    HAL_GPIO_WritePin(GPIOA, GREENLED, 0);
    HAL_GPIO_WritePin(GPIOA, LOCK, 0);
    HAL_GPIO_WritePin(GPIOA, BUZZER, 0);
}
