/*
 * gpio.h
 *
 *  Created on: Nov 1, 2023
 *      Author: dell
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"
// LED status
#define REDLED 	 GPIO_PIN_0
#define GREENLED GPIO_PIN_1

//Solenoid Lock
#define LOCK      GPIO_PIN_11

//Buzzer
#define BUZZER      GPIO_PIN_2

void gpio_Init(void);
#endif /* INC_GPIO_H_ */
