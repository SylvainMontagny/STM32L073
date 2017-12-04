/*
 * gpio.h
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "main.h"
#include "stm32l0xx_hal.h"

void test_gpio(state mode);

/***** Variables externes *****/
extern char msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;

#endif /* GPIO_H_ */
