/*
 * stm32f1xx_it.h
 *
 *  Created on: Oct 18, 2023
 *      Author: dell
 */
#include "main.h"
#include "stm32f1xx_it.h"
void SysTick_Handler(void)
{
    HAL_IncTick();
}

// External EXTI15_10 callback
void EXTI15_10_IRQHandler(void)
{
    if (__HAL_GPIO_EXTI_GET_IT(ENTER) != RESET)
    {
    	HAL_GPIO_EXTI_IRQHandler(ENTER);
    }
    if (__HAL_GPIO_EXTI_GET_IT(DOWN) != RESET)
    {
    	HAL_GPIO_EXTI_IRQHandler(DOWN);
    }
}


