/*
 * exti.h
 *
 *  Created on: Nov 1, 2023
 *      Author: dell
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "main.h"
#define BUTTON_PORT GPIOB
#define ENTER GPIO_PIN_12
#define DOWN GPIO_PIN_13
void exti_buttonConfig(void);

#endif /* INC_EXTI_H_ */
