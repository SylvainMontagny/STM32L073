/*
 * rtc.h
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#ifndef RTC_H_
#define RTC_H_

#include "main.h"
#include "stm32l0xx_hal.h"

void test_rtc(state etat);

/***** Buffer UART2 *****/
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

/***** Variables Gestion UART2 *****/
extern uint8_t UART2_IsStringValid;

/***** Variables Gestion sortie des Etats *****/
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;

/***** Handle UART2, RTC *****/
extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;

/***** Variables Gestion RTC *****/
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;

#endif /* RTC_H_ */
