/*
 * adc.h
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"
#include "stm32l0xx_hal.h"

/**** Adresses des valeurs de calibration du Temperature sensor *****/
#define TS_CAL1_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007A))
#define TS_CAL2_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007E))

void test_adc(state etat);

/***** Buffer UART2 *****/
extern uint8_t tx_buffer_uart[TAILLE_BUF_UART_TX];
extern uint8_t rx_buffer_uart[TAILLE_BUF_UART_RX];

/***** Variables Gestion UART2 *****/
extern uint8_t UART2_IsStringValid;

/***** Variables Gestion sortie des Etats *****/
extern uint8_t AttenteSortieEtat;
extern volatile uint8_t SortieEtat;


/***** Handle UART2, ADC, DAC *****/
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef  hadc;
extern DAC_HandleTypeDef  hdac;

#endif /* ADC_H_ */
