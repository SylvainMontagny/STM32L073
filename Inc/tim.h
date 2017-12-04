/*
 * tim.h
 *
 *  Created on: 24 nov. 2017
 *      Author: Sylvain
 */

#ifndef TIM_H_
#define TIM_H_

#include "main.h"
#include "stm32l0xx_hal.h"

void test_basic_tim6(void);
void test_input_capture_tim3(void);

/***** Variables externes *****/
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern char msg[TAILLE_BUF];
extern uint8_t ready;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t captureDone;
extern uint16_t captures[2];

#endif /* TIM_H_ */
