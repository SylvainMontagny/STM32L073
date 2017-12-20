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
void print_menu_uart(void);
void print_menu_timer(void);
void VirtualCOM_Transmit( char *format, ... );

extern state etat_courant;

/***** Buffer UART2, LPUART, SPI *****/
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

/***** Variables Gestion UART2 *****/
extern uint8_t UART2_IsStringValid;
extern uint8_t UART2_CaractereRecu;

/***** Handle UART2 *****/
extern UART_HandleTypeDef huart2;

#endif /* PRINT_MENU_H_ */
