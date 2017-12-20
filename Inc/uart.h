/*
 * uart.h
 *
 *  Created on: 11 déc. 2017
 *      Author: Sylvain
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"
#include "stm32l0xx_hal.h"



void test_uart(state etat);

/***** Variables externes *****/
extern uint8_t ready;
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;
extern uint8_t lpuart_IT_Received;
extern uint8_t lpuart_DMA_Received;

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];
extern uint8_t rx_buffer_lpuart[TAILLE_BUF_LPUART_RX];
extern uint8_t tx_buffer_lpuart[TAILLE_BUF_LPUART_TX];

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hlpuart1;


#endif /* UART_H_ */
