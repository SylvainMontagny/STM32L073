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

extern state etat_courant;

/***** Buffer UART2, LPUART, SPI *****/
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];
extern uint8_t rx_buffer_lpuart[TAILLE_BUF_LPUART_RX];
extern uint8_t tx_buffer_lpuart[TAILLE_BUF_LPUART_TX];
extern uint8_t rx_buffer_spi[TAILLE_BUF_SPI];
extern uint8_t tx_buffer_spi[TAILLE_BUF_SPI];

/***** Variables Gestion UART2 *****/
extern uint8_t UART2_CaractereRecu;
extern uint8_t UART2_IsStringValid;
extern uint32_t UART2_NbrCaractereRecu;

/***** variables Gestion Input Captur TIM3  *****/
extern uint8_t IC_IsCaptureDone;
extern uint8_t IC_PA11Calculate;
extern uint8_t IC_PA11Start;

/***** Variables Gestion LPUART *****/
extern uint8_t LPUART_IsITReceived;
extern uint8_t LPUART_IsDMAReceived;

/***** Variables Gestion sortie des Etats *****/
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;

/***** Handle UART2, LPUART *****/
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hlpuart1;

/***** Variables Gestion RTC *****/
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;

#endif /* CALLBACK_H_ */
