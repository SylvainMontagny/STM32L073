/*
 * print_menu.c
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#include "print_menu.h"

void print_menu(void){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n\r\n***** Programme TEST des périphériques *****\r\n ");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(g) GPIO\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(a) ADC\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(r) RTC\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(b) Basic Timer TIM6\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(i) Input Capture TIM3\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\t(s) SPI\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);

	/***** Activation IT UART2 RX *****/
	HAL_UART_Receive_IT(&huart2,&caractere,1);
	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(	rx_buffer_uart[0]!='g' && rx_buffer_uart[0]!='a' &&
			rx_buffer_uart[0]!='r' && rx_buffer_uart[0]!='b' &&
			rx_buffer_uart[0]!='i' && rx_buffer_uart[0]!='s');

	switch(rx_buffer_uart[0]){
		case 'g' :etat_courant=MENU_GPIO_PRINT;			break;
		case 'a' :etat_courant=MENU_ADC_PRINT;			break;
		case 'r' :etat_courant=MENU_RTC_PRINT;			break;
		case 'b' :etat_courant=TEST_BASIC_TIM6;			break;
		case 'i' :etat_courant=TEST_INPUT_CAPTURE_TIM3;	break;
		case 's' :etat_courant=TEST_SPI;				break;
	}

}



void print_menu_gpio(){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n***** Test des GPIO ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(P) Mode Polling (scrutation)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(I) Mode IT (Interruption)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer_uart[0]!='P' && rx_buffer_uart[0]!='I' && rx_buffer_uart[0]!='c');

	switch(rx_buffer_uart[0]){
		case 'P' :etat_courant=TEST_GPIO_POLLING;	break;
		case 'I' :etat_courant=TEST_GPIO_IT;		break;
		case 'c' :etat_courant=MENU_START_PRINT; 	break;
	}

}


void print_menu_rtc(){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n***** Test de la RTC ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(G) Get Date-Heure\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(S) Set Date-Heure\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(A) Alarme (IT) toutes les secondes\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer_uart[0]!='G' && rx_buffer_uart[0]!='S' && rx_buffer_uart[0]!='A' && rx_buffer_uart[0]!='c');

	switch(rx_buffer_uart[0]){
		case 'G' :etat_courant=TEST_RTC_GET;		break;
		case 'S' :etat_courant=TEST_RTC_SET;		break;
		case 'A' :etat_courant=TEST_RTC_ALARM;		break;
		case 'c' :etat_courant=MENU_START_PRINT; 	break;
	}

}

void print_menu_adc(void){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n***** Test de l'ADC ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(I) IN0 Channel : PA0 (A0 Nucléo)\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(T) Temperature Internal\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"(C) Calibration ADC\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	/***** Test sortie du menu *****/
	do{
			while(ready!=1);
			ready=0;
		}
		while(rx_buffer_uart[0]!='I' && rx_buffer_uart[0]!='T' && rx_buffer_uart[0]!='C' && rx_buffer_uart[0]!='c');

		switch(rx_buffer_uart[0]){
			case 'I' :etat_courant=TEST_ADC_IN0;			break;
			case 'T' :etat_courant=TEST_ADC_TEMPERATURE;	break;
			case 'C' :etat_courant=TEST_ADC_CALIB;			break;
			case 'c' :etat_courant=MENU_START_PRINT; 		break;
		}
}

