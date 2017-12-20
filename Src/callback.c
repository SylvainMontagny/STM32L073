/*
 * utilities.c
 *
 *  Created on: 4 déc. 2017
 *      Author: Sylvain
 */

#include "callback.h"




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

if(huart==&huart2){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	PRINTF("%c",caractere);
	rx_buffer_uart[nbr_caractere]=caractere;
	nbr_caractere++;
/***** Si on recoit '\b' *****/
	if(caractere=='\b'){
		nbr_caractere--;
		PRINTF(" \b");
	}

/***** Si on recoit 13 *****/
	if(caractere==13){
		PRINTF("\r\n");
		ready=1;
		/***** TEST_RTC_SET : Attente de 8 caractere *****/
		if(etat_courant==TEST_RTC_SET && nbr_caractere!=9 && AttenteSortieEtat!=1){
				ready=0;
				PRINTF("Nombre de caractere saisi invalide\r\n");
			}
		/***** Attente d'un seul caractere dans tous les menus *****/
		if( 	(( etat_courant==MENU_START_PRINT || etat_courant==MENU_GPIO_PRINT ||
				  etat_courant==MENU_ADC_PRINT   || etat_courant==MENU_RTC_PRINT  ||
				  etat_courant==MENU_TIMER_PRINT || etat_courant==MENU_UART_PRINT ) && nbr_caractere!=2)){
			ready=0;
		}
		else{

		}
		/***** Sortie d'état : Attente de 'c' *****/
		if(AttenteSortieEtat==1 && nbr_caractere==2 && rx_buffer_uart[0]=='c'){
				SortieEtat=1;
				ready=0;
			}

		nbr_caractere=0;
	}
/***** Gestion Buffer Reception *****/
	if(nbr_caractere==TAILLE_BUF_UART_RX){
		nbr_caractere=0;
	}
/***** Relance d'interruption prochain caractère *****/
	if(HAL_UART_Receive_IT(&huart2,&caractere,1) != HAL_OK) PRINTF("\n HAL_UART_IT NOK\n");
}


else if(huart==&hlpuart1){
	switch(etat_courant){
		case	TEST_UART_IT :
			PRINTF("\r\nLP_UART Receive (INTERRUPT) :\t%s\r\n",rx_buffer_lpuart);
			lpuart_IT_Received=1;
		break;

		case 	TEST_UART_DMA :
			PRINTF("\r\nLP_UART Receive  (DMA) :\t%s\r\n",rx_buffer_lpuart);
			lpuart_DMA_Received=1;
		break;
	}
}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin==GPIO_PIN_13){
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		PRINTF("IT BP Pin PC13 (Rising Edge) \r\n");

	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	/***** Récupération Time et Date *****/
	HAL_RTC_GetTime(hrtc,&my_time,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc,&my_date,RTC_FORMAT_BIN);					// GetDate doit obligatoirement suivre un GetTime, sinon GetTime reste à la meme valeur
	PRINTF("RTC interrupt \t\t Time : %02u:%02u:%02u                   \r\n",my_time.Hours,my_time.Minutes,my_time.Seconds);
	HAL_RTC_GetTime(hrtc,& my_time,RTC_FORMAT_BIN);			// hrtc et non pas &hrtc (hrtc est ici une variable locale)
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(etat_courant == TEST_TIM3_IC_PA6){
		captureDone=1;
	}else {
		InputCapturePA11Start=0;
		InputCapturePA11Calculate=1;
		}
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	PRINTF("\r\nPassage dans IT DMA (SPI)\r\n");
	/***** Buffer RX et TX APRES transmission *****/
	PRINTF("+------------------------------------------------------+\r\n");
	PRINTF("| TX | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u |\r\n", tx_buffer_spi[0],tx_buffer_spi[1],tx_buffer_spi[2],tx_buffer_spi[3],tx_buffer_spi[4],tx_buffer_spi[5],tx_buffer_spi[6],tx_buffer_spi[7],tx_buffer_spi[8],tx_buffer_spi[9]);
	PRINTF("+------------------------------------------------------+\r\n");
	PRINTF("| RX | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u |\r\n", rx_buffer_spi[0],rx_buffer_spi[1],rx_buffer_spi[2],rx_buffer_spi[3],rx_buffer_spi[4],rx_buffer_spi[5],rx_buffer_spi[6],rx_buffer_spi[7],rx_buffer_spi[8],rx_buffer_spi[9]);
	PRINTF("+------------------------------------------------------+\r\n");
}

/*void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	PRINTF("Passage dans IT DMA (SPI)\r\n");
	
	transmit_SPI_Done=1;
}*/
