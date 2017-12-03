/*
 * peripheral.c
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */
#include <gpio.h>
#include "stm32l0xx_hal.h"
#include "main.h"
#include "gpio.h"

void test_gpio(state mode);

extern uint8_t msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;



void test_gpio(state mode){
	uint32_t sortir_etat=0;
	GPIO_InitTypeDef GPIO_InitStruct;



	switch(mode){
	case TEST_GPIO_IT :
		snprintf(msg,TAILLE_BUF,"Mode Interruption\r\nUn appuis sur le BP (USER) Toggle la LED (LD3) \r\n");
		HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		/*Configure GPIO pin : PC13 */
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
		//HAL_NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
		HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);


		do{
				while(ready!=1);
				ready=0;
			}
			while(rx_buffer[0]!='c');
		HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);
		break;

	case TEST_GPIO_POLLING :
		snprintf(msg,TAILLE_BUF,"Mode Scrutation\r\nLED (LD3) allumée si BP (USER) appuyé\r\n");
		HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		/*Configure GPIO pin : PC13 */
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		sortir_etat=0;
		ready=0;
		while(sortir_etat==0){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13));
			if(	(ready==1) && (rx_buffer[0]=='c')	){
				sortir_etat=1;
			}
			else{
				ready=0;		// mais on reste dans le mode GPIO_POLLING
			}
		}
		ready=0;
		break;

	}
}


