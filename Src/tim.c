/*
 * tim.c
 *
 *  Created on: 24 nov. 2017
 *      Author: Sylvain
 */
#include "stm32l0xx_hal.h"
#include "main.h"
#include "tim.h"


extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern uint8_t msg[TAILLE_BUF];
extern uint8_t ready;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint32_t captureDone;
extern uint16_t captures[2];

void test_basic_tim6(void){
	snprintf(msg,TAILLE_BUF,"\r\n***** Test Basic TIM6 ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"***** Clignotement USER LED par IT TIM6 *****\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	HAL_TIM_Base_Start_IT(&htim6);
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer[0]!='c');
	HAL_TIM_Base_Stop_IT(&htim6);

}


void test_input_capture_tim3(void){
	uint32_t diffCapture;
	float frequency;
	snprintf(msg,TAILLE_BUF,"\r\n***** Test Input Capture TIM3 ***** \r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"***** Mesure Fréquence sur broche PA6 *****\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);

	HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1, captures,2);			// Demarrage du DMA pour capture de 2 fronts montants
	HAL_TIM_Base_Start_IT(&htim6);									// Demarrage de TIM6 pour clignotement LED si on souhaite mesurer la fréquence de de PA5 (LED)

	while(captureDone==0);											// Capture

	HAL_TIM_Base_Stop_IT(&htim6);									// Arrêt TIM6

	if(captures[0]<captures[1]){
		diffCapture=captures[1]-captures[0];
	}
	if(captures[0]>captures[1]){
		diffCapture=htim3.Instance->ARR - (captures[0]-captures[1]);
	}
	frequency= (float)(HAL_RCC_GetPCLK1Freq()) / (float)(htim3.Instance->PSC + 1);
	frequency=frequency /diffCapture;
	snprintf(msg,TAILLE_BUF,"Capture 0 : %d \r\nCapture 1 : %d\r\nCalcul Frequence : %.3f Hertz \r\n", captures[0], captures[1], frequency);
	HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
	HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);						// Arrêt du DMA
	captureDone=0;
}

