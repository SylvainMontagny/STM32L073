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
	if(nbr_caractere==TAILLE_BUF_UART_RX){
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
		rx_buffer_uart[nbr_caractere]=0;
		if( !( ( (etat_courant!=TEST_RTC_SET) && (etat_courant!=TEST_ADC_IN0) ) && (nbr_caractere!=1) ) ) {
			ready=1;
		}
		nbr_caractere=0;
	}
	else{
		rx_buffer_uart[nbr_caractere]=caractere;
		nbr_caractere++;
	}
	/***** Relance d'interruption prochain caractère *****/
	HAL_UART_Receive_IT(&huart2,&caractere,1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin==GPIO_PIN_13){
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"IT BP Pin PC13 (Rising Edge) \r\n");
		HAL_UART_Transmit(&huart2,(uint8_t *)tx_buffer_uart,strlen(tx_buffer_uart),1000);
	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	/***** Récupération Time et Date *****/
	HAL_RTC_GetTime(hrtc,&my_time,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc,&my_date,RTC_FORMAT_BIN);					// GetDate doit obligatoirement suivre un GetTime, sinon GetTime reste à la meme valeur
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"RTC interrupt \t\t Time : %02u:%02u:%02u                   \r\n",my_time.Hours,my_time.Minutes,my_time.Seconds);
	HAL_UART_Transmit(&huart2,(uint8_t *)tx_buffer_uart,strlen(tx_buffer_uart),1000);
	HAL_RTC_GetTime(hrtc,& my_time,RTC_FORMAT_BIN);			// hrtc et non pas &hrtc (hrtc est ici une variable locale)
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Passage dans IT DMA (Input Capture)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
	captureDone=1;
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nPassage dans IT DMA (SPI)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);

	/***** Buffer RX et TX APRES transmission *****/
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nBuffer RX et TX après transmission :\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"TX : %2u %2u %2u %2u %2u %2u %2u %2u %2u %2u\r\n", tx_buffer_spi[0],tx_buffer_spi[1],tx_buffer_spi[2],tx_buffer_spi[3],tx_buffer_spi[4],tx_buffer_spi[5],tx_buffer_spi[6],tx_buffer_spi[7],tx_buffer_spi[8],tx_buffer_spi[9]);
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"RX : %2u %2u %2u %2u %2u %2u %2u %2u %2u %2u\r\n", rx_buffer_spi[0],rx_buffer_spi[1],rx_buffer_spi[2],rx_buffer_spi[3],rx_buffer_spi[4],rx_buffer_spi[5],rx_buffer_spi[6],rx_buffer_spi[7],rx_buffer_spi[8],rx_buffer_spi[9]);
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
}

/*void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Passage dans IT DMA (SPI)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
	transmit_SPI_Done=1;
}*/
