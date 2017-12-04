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

extern char msg[TAILLE_BUF];

extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;
extern uint8_t caractere;

extern state etat_courant;

extern UART_HandleTypeDef huart2;

void print_menu(void);
void print_menu_gpio(void);
void print_menu_rtc(void);
void print_menu_adc(void);

#endif /* PRINT_MENU_H_ */
