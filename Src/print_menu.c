/*
 * print_menu.c
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#include "print_menu.h"
#include "stm32l0xx_hal.h"
#include "main.h"

extern uint8_t msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;
extern uint8_t caractere;
extern state etat_courant;

void print_menu(void){
	snprintf(msg,TAILLE_BUF,"\r\n\r\n***** Programme TEST des périphériques *****\r\n ");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"\t(g) GPIO\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"\t(a) ADC\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"\t(r) RTC\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"\t(b) Basic Timer TIM6\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"\t(i) Input Capture TIM3\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);

	HAL_UART_Receive_IT(&huart2,&caractere,1);

	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer[0]!='g' && rx_buffer[0]!='a' && rx_buffer[0]!='r' && rx_buffer[0]!='b' && rx_buffer[0]!='i');

	switch(rx_buffer[0]){
		case 'g' :etat_courant=MENU_GPIO_PRINT;	break;
		case 'a' :etat_courant=MENU_ADC_PRINT;	break;
		case 'r' :etat_courant=MENU_RTC_PRINT;	break;
		case 'b' :etat_courant=TEST_BASIC_TIM6;	break;
		case 'i' :etat_courant=TEST_INPUT_CAPTURE_TIM3;	break;
	}

}



void print_menu_gpio(){
	snprintf(msg,TAILLE_BUF,"\r\n***** Test des GPIO ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(P) Mode Polling (scrutation)\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(I) Mode IT (Interruption)\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);

	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer[0]!='P' && rx_buffer[0]!='I' &&rx_buffer[0]!='c');

	switch(rx_buffer[0]){
		case 'P' :etat_courant=TEST_GPIO_POLLING;	break;
		case 'I' :etat_courant=TEST_GPIO_IT;	break;
		case 'c' :etat_courant=MENU_START_PRINT; break;
	}

}


void print_menu_rtc(){
	snprintf(msg,TAILLE_BUF,"\r\n***** Test de la RTC ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(G) Get Date-Heure\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(S) Set Date-Heure\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(A) Alarme (IT) toutes les secondes\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);


	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer[0]!='G' && rx_buffer[0]!='S' && rx_buffer[0]!='A' && rx_buffer[0]!='c');

	switch(rx_buffer[0]){
		case 'G' :etat_courant=TEST_RTC_GET;	break;
		case 'S' :etat_courant=TEST_RTC_SET;	break;
		case 'A' :etat_courant=TEST_RTC_ALARM;	break;
		case 'c' :etat_courant=MENU_START_PRINT; break;
	}

}

void print_menu_adc(void){
	snprintf(msg,TAILLE_BUF,"\r\n***** Test de l'ADC ***** Touche 'c' pour sortir\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(I) IN0 Channel : PA0 (A0 Nucléo)\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(T) Temperature Internal\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
	snprintf(msg,TAILLE_BUF,"(C) Calibration ADC\r\n");
	HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);

	do{
			while(ready!=1);
			ready=0;
		}
		while(rx_buffer[0]!='I' && rx_buffer[0]!='T' && rx_buffer[0]!='C' && rx_buffer[0]!='c');

		switch(rx_buffer[0]){
			case 'I' :etat_courant=TEST_ADC_IN0;			break;
			case 'T' :etat_courant=TEST_ADC_TEMPERATURE;	break;
			case 'C' :etat_courant=TEST_ADC_CALIB;			break;
			case 'c' :etat_courant=MENU_START_PRINT; 		break;
		}

}

