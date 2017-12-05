/*
 * spi.h
 *
 *  Created on: 5 déc. 2017
 *      Author: Sylvain
 */

#ifndef SPI_H_
#define SPI_H_

#include "main.h"
#include "stm32l0xx_hal.h"

void test_spi(void);

/***** Variables externes *****/

extern uint8_t rx_buffer_spi[TAILLE_BUF_SPI];
extern uint8_t tx_buffer_spi[TAILLE_BUF_SPI];

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

extern UART_HandleTypeDef huart2;
extern SPI_HandleTypeDef hspi2;

#endif /* SPI_H_ */
