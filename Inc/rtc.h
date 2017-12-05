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

/***** Variables externes *****/
extern uint8_t ready;

extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;

#endif /* RTC_H_ */
