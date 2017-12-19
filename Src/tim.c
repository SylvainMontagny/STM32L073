/*
 * tim.c
 *
 *  Created on: 24 nov. 2017
 *      Author: Sylvain
 */

#include "tim.h"

void test_timer(state etat){
	uint32_t diffCapture;
	uint32_t sortir_etat=0;
	float frequency;

	int i; //test

	switch(etat){
		case TEST_TIM6_BASIC :
			PRINTF(RED);
			PRINTF("\r\n***** Test Basic TIM6 ***** Touche 'c' pour sortir\r\n");
			PRINTF("***** Clignotement USER LED par IT TIM6 *****\r\n");
			PRINTF(BLACK);
			/***** D�marrage TIM6 en interruption *****/
			HAL_TIM_Base_Start_IT(&htim6);

			/***** Test sortie du menu *****/
			do{
				while(ready!=1);
				ready=0;
			}
			while(rx_buffer_uart[0]!='c');

			/***** Sortie du menu *****/
			HAL_TIM_Base_Stop_IT(&htim6);
		break;
	
		case TEST_TIM3_IC_PA6 :
			PRINTF(RED);
			PRINTF("\r\n***** Test Input Capture TIM3 ***** \r\n");
			PRINTF("***** Mesure Fr�quence sur broche PA6 *****\r\n");
			PRINTF(BLACK);
			while(sortir_etat==0){
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
				//PRINTF("frequency timer : %.f\r\n",frequency);
				frequency=frequency /diffCapture;
				PRINTF("Capture 0 : %7u \r\nCapture 1 : %7u\r\n", captures[0], captures[1]);
				PRINTF("Frequence : %7.3f Hertz \r\n",frequency);
				PRINTF("Temps     : %7u �s \r\n\r\n",(uint32_t)(1/frequency*1000000));
				HAL_Delay(2500);
				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
		break;

		case TEST_TIM3_IC_PA11 :
			if(InputCapturePA11Start==1){
				PRINTF(RED);
				PRINTF("\r\n***** Test Input Capture TIM3 ***** \r\n");
				PRINTF("***** Mesure Fr�quence sur broche PA11 *****\r\n");
				PRINTF(BLACK);
				/***** Input Capture en Mode DMA *****/
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
				HAL_TIM_IC_Start_DMA(&htim3,TIM_CHANNEL_1, captures,2);			// Demarrage du DMA pour capture de 2 fronts montants
			}
			else if(InputCapturePA11Calculate==1){
				HAL_TIM_IC_Stop_DMA(&htim3,TIM_CHANNEL_1);						// Arr�t du DMA

				/***** Calcul et affichage *****/
				if(captures[0]<=captures[1]){
					diffCapture=captures[1]-captures[0];
				}
				if(captures[0]>captures[1]){
					diffCapture=htim3.Instance->ARR - (captures[0]-captures[1]);
				}
				frequency= (float)(HAL_RCC_GetPCLK1Freq()) / (float)(htim3.Instance->PSC + 1);
				//PRINTF("frequency timer : %.f\r\n",frequency);
				frequency=frequency /diffCapture;
				PRINTF("Capture 0 : %7u \r\nCapture 1 : %7u\r\n", captures[0], captures[1]);
				PRINTF("Frequence : %7.3f Hertz \r\n",frequency);
				PRINTF("Temps     : %7u �s \r\n\r\n",(uint32_t)(1/frequency*1000000));
				InputCapturePA11Start=1;
				InputCapturePA11Calculate=0;

			}

			START_MESURE;
			//frequency=captures[0]*captures[1];
			i++;//for(i=0;i<1;i++);
			//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
			STOP_MESURE;

		break;
	}
}

