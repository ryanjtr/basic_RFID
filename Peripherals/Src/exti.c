/*
 * exti.c
 *
 *  Created on: Nov 1, 2023
 *      Author: dell
 */

#include "exti.h"

void exti_buttonConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ENTER | DOWN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING ;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);

    //Enable Interupt
    HAL_NVIC_SetPriority(EXTI15_10_IRQn ,0,0);// Đặt ưu tiên cho các ngắt EXTI
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);// Kích hoạt ngắt EXTI
}
