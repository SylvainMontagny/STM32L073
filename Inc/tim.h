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

/***** Buffer UART2 *****/
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

/***** Variables Gestion UART2 *****/
extern uint8_t UART2_IsStringValid;

/***** variables Gestion Input Captur TIM3  *****/
extern uint8_t  IC_IsCaptureDone;
extern uint8_t  IC_PA11Calculate;
extern uint8_t  IC_PA11Start;
extern uint16_t IC_Captures[2];

/***** Variables Gestion sortie des Etats *****/
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;

/***** Handle UART2, TIM3, TIM6 *****/
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

#endif /* TIM_H_ */
