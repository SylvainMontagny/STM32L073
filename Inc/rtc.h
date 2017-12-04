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
extern char msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;
extern RTC_HandleTypeDef hrtc;
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;

#endif /* RTC_H_ */
