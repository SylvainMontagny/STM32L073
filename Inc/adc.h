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

/**** Adresse des valeurs de calibration du Temperature sensor *****/
#define TS_CAL1_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007A))
#define TS_CAL2_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007E))

void test_adc(state mode);

/***** Variables externes *****/
extern char msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc;
extern DAC_HandleTypeDef hdac;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;

#endif /* ADC_H_ */
