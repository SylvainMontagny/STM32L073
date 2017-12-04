/*
 * peripheral.c
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#include "gpio.h"

void test_gpio(state etat){
	uint32_t sortir_etat=0;
	GPIO_InitTypeDef GPIO_InitStruct;

	switch(etat){
	case TEST_GPIO_POLLING :
		snprintf(msg,TAILLE_BUF,"Mode Scrutation\r\nLED (LD3) allum�e si BP (USER) appuy�\r\n");
		HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
		/***** Configuration PIN PC13 en Input *****/
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		/***** Test sortie menu *****/
		while(sortir_etat==0){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,!HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13));
			if(ready==1){
				ready=0;
				if(rx_buffer[0]=='c'){
					sortir_etat=1;
				}
			}
		}
		/***** Sortie du menu *****/
		break;

	case TEST_GPIO_IT :
		snprintf(msg,TAILLE_BUF,"Mode Interruption\r\nUn appuis sur le BP (USER) Toggle la LED (LD3) \r\n");
		HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
		/***** Configuration PIN PC13 en IT *****/
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
		HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
		/***** Test sortie menu *****/
		do{
				while(ready!=1);
				ready=0;
		}
		while(rx_buffer[0]!='c');
		/**** Sortie du menu *****/
		HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);
		break;

	default:
		break;
	}
}


