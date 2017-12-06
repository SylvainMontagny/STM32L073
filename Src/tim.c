/*
 * tim.c
 *
 *  Created on: 24 nov. 2017
 *      Author: Sylvain
 */

#include "tim.h"


void test_basic_tim6(void){
	PRINTF("\r\n***** Test Basic TIM6 ***** Touche 'c' pour sortir\r\n");
	PRINTF("***** Clignotement USER LED par IT TIM6 *****\r\n");
	
	/***** D�marrage TIM6 en int�rruption *****/
	HAL_TIM_Base_Start_IT(&htim6);

	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer_uart[0]!='c');

	/***** Sortie du menu *****/
	HAL_TIM_Base_Stop_IT(&htim6);
}


void test_input_capture_tim3(void){
	uint32_t diffCapture;
	float frequency;
	PRINTF("\r\n***** Test Input Capture TIM3 ***** \r\n");
	PRINTF("***** Mesure Fr�quence sur broche PA6 *****\r\n");
	
	/***** Input Capture en Mode DMA *****/
	HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1, captures,2);			// Demarrage du DMA pour capture de 2 fronts montants
	HAL_TIM_Base_Start_IT(&htim6);									// Demarrage de TIM6 pour clignotement LED si on souhaite mesurer la fr�quence de PA5 (LED)
	while(captureDone==0);
	captureDone=0;
	HAL_TIM_Base_Stop_IT(&htim6);									// Arr�t TIM6
	HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);						// Arr�t du DMA

	/***** Calcul et affichage *****/
	if(captures[0]<=captures[1]){
		diffCapture=captures[1]-captures[0];
	}
	if(captures[0]>captures[1]){
		diffCapture=htim3.Instance->ARR - (captures[0]-captures[1]);
	}
	frequency= (float)(HAL_RCC_GetPCLK1Freq()) / (float)(htim3.Instance->PSC + 1);
	frequency=frequency /diffCapture;
	PRINTF("Capture 0 : %4u \r\nCapture 1 : %4u\r\nCalcul Frequence : %.3f Hertz \r\n", captures[0], captures[1], frequency);
	
}

