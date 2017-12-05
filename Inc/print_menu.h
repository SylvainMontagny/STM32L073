/*
 * printf_menu.h
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#ifndef PRINT_MENU_H_
#define PRINT_MENU_H_

#include "main.h"
#include "stm32l0xx_hal.h"

void print_menu(void);
void print_menu_gpio(void);
void print_menu_rtc(void);
void print_menu_adc(void);

/***** Variables externes *****/
extern uint8_t ready;
extern uint8_t caractere;
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

extern state etat_courant;

extern UART_HandleTypeDef huart2;

#endif /* PRINT_MENU_H_ */
