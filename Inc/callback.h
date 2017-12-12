/*
 * utilities.h
 *
 *  Created on: 4 déc. 2017
 *      Author: Sylvain
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "main.h"
#include "stm32l0xx_hal.h"

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hlpuart1;

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];
extern uint8_t rx_buffer_lpuart[TAILLE_BUF_LPUART_RX];
extern uint8_t tx_buffer_lpuart[TAILLE_BUF_LPUART_TX];

extern uint8_t rx_buffer_spi[TAILLE_BUF_SPI];
extern uint8_t tx_buffer_spi[TAILLE_BUF_SPI];

extern uint8_t caractere;
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];
extern uint8_t captureDone;
extern uint8_t ready;
extern uint8_t lpuart_IT_Received;

extern uint32_t nbr_caractere;


extern state etat_courant;
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;

#endif /* CALLBACK_H_ */
