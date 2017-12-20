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

void test_gpio(state etat);

/***** Variables externes *****/
extern uint8_t ready;
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

extern UART_HandleTypeDef huart2;
#endif /* GPIO_H_ */
