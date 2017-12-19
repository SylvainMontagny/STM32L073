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

void test_timer(state etat);

/***** Variables externes *****/
extern uint8_t ready;
extern uint8_t captureDone;
extern uint8_t InputCapturePA11Calculate;
extern uint8_t InputCapturePA11Start;

extern uint16_t captures[2];

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

#endif /* TIM_H_ */
