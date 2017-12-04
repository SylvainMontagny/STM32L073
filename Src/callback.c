/*
 * utilities.c
 *
 *  Created on: 4 déc. 2017
 *      Author: Sylvain
 */

#include "callback.h"




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	/***** Toggle LED et affichage caractere saisi *****/
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	HAL_UART_Transmit(&huart2,&caractere,1,100);
	/***** Gestion débordement du buffer d'entrée *****/
	if(nbr_caractere==TAILLE_BUF){
		nbr_caractere=0;
	}
	/***** Gestion du backspace pour suppréssion saisie *****/
	if(caractere=='\b'){
		if(nbr_caractere!=0) {
			nbr_caractere--;
		}
		HAL_UART_Transmit(&huart2," \b",2,100);
	}
	/***** Gestion validation de la saisie *****/
	else if(caractere==13){
		HAL_UART_Transmit(&huart2,(uint8_t *)"\r\n",2,100);
		rx_buffer[nbr_caractere]=0;
		if( !( ( (etat_courant!=TEST_RTC_SET) && (etat_courant!=TEST_ADC_IN0) ) && (nbr_caractere!=1) ) ) {
			ready=1;
		}
		nbr_caractere=0;
	}
	else{
		rx_buffer[nbr_caractere]=caractere;
		nbr_caractere++;
	}
	/***** Relance d'interruption prochain caractère *****/
	HAL_UART_Receive_IT(&huart2,&caractere,1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin==GPIO_PIN_13){
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		snprintf(msg,TAILLE_BUF,"IT BP Pin PC13 (Rising Edge) \r\n");
		HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	/***** Récupération Time et Date *****/
	HAL_RTC_GetTime(hrtc,&my_time,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc,&my_date,RTC_FORMAT_BIN);					// GetDate doit obligatoirement suivre un GetTime, sinon GetTime reste à la meme valeur
	snprintf(msg,TAILLE_BUF,"RTC interrupt \t\t Time : %02u:%02u:%02u                   \r\n",my_time.Hours,my_time.Minutes,my_time.Seconds);
	HAL_UART_Transmit(&huart2,(uint8_t *)msg,strlen(msg),1000);
	HAL_RTC_GetTime(hrtc,& my_time,RTC_FORMAT_BIN);			// hrtc et non pas &hrtc (hrtc est ici une variable locale)
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	snprintf(msg,TAILLE_BUF,"Passage IT DMA\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
	captureDone=1;
}

