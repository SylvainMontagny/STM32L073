/*
 * print_menu.c
 *
 *  Created on: 16 nov. 2017
 *      Author: Sylvain
 */

#include "print_menu.h"

void print_menu(void){
	PRINTF("\r\n\r\n***** Programme TEST des périphériques *****\r\n ");
	PRINTF("\t(g) GPIO\r\n");
	PRINTF("\t(a) ADC\r\n");
	PRINTF("\t(r) RTC\r\n");
	PRINTF("\t(t) TIMER\r\n");
	PRINTF("\t(s) SPI\r\n");
	PRINTF("\t(u) UART\r\n");

	/***** Activation IT UART2 RX *****/
	HAL_UART_Receive_IT(&huart2,&caractere,1);
	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(	rx_buffer_uart[0]!='g' && rx_buffer_uart[0]!='a' &&
			rx_buffer_uart[0]!='r' && rx_buffer_uart[0]!='t' &&
			rx_buffer_uart[0]!='s' && rx_buffer_uart[0]!='u');

	switch(rx_buffer_uart[0]){
		case 'g' :etat_courant=MENU_GPIO_PRINT;			break;
		case 'a' :etat_courant=MENU_ADC_PRINT;			break;
		case 'r' :etat_courant=MENU_RTC_PRINT;			break;
		case 't' :etat_courant=MENU_TIMER_PRINT;		break;
		case 's' :etat_courant=TEST_SPI;				break;
		case 'u' :etat_courant=MENU_UART_PRINT;			break;
	}

}


void print_menu_gpio(){
	PRINTF("\r\n***** Test des GPIO ***** Touche 'c' pour sortir\r\n");
	PRINTF("(P) Mode Polling (scrutation)\r\n");
	PRINTF("(I) Mode Interrupt (Interruption)\r\n");

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
	PRINTF("\r\n***** Test de la RTC ***** Touche 'c' pour sortir\r\n");
	PRINTF("(G) Get Date-Heure\r\n");
	PRINTF("(S) Set Date-Heure\r\n");
	PRINTF("(A) Alarme (IT) toutes les secondes\r\n");

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
	PRINTF("\r\n***** Test de l'ADC ***** Touche 'c' pour sortir\r\n");
	PRINTF("(I) IN1 Channel : PA0 (A0 Nucléo)\r\n");
	PRINTF("(T) Temperature Internal\r\n");
	PRINTF("(C) Calibration ADC\r\n");

	/***** Test sortie du menu *****/
	do{
			while(ready!=1);
			ready=0;
		}
		while(rx_buffer_uart[0]!='I' && rx_buffer_uart[0]!='T' && rx_buffer_uart[0]!='C' && rx_buffer_uart[0]!='c');

		switch(rx_buffer_uart[0]){
			case 'I' :etat_courant=TEST_ADC_IN1;			break;
			case 'T' :etat_courant=TEST_ADC_TEMPERATURE;	break;
			case 'C' :etat_courant=TEST_ADC_CALIB;			break;
			case 'c' :etat_courant=MENU_START_PRINT; 		break;
		}
}


void print_menu_uart(){
	PRINTF("\r\n***** Test UART (Low Power) ***** Touche 'c' pour sortir\r\n");
	PRINTF("(P) Mode Polling (scrutation)\r\n");
	PRINTF("(I) Mode Iterrupt (Interruption)\r\n");
	PRINTF("(D) Mode DMA\r\n");

	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer_uart[0]!='P' && rx_buffer_uart[0]!='I' && rx_buffer_uart[0]!='D' && rx_buffer_uart[0]!='c');

	switch(rx_buffer_uart[0]){
		case 'P' :etat_courant=TEST_UART_POLLING;	break;
		case 'I' :etat_courant=TEST_UART_IT;		break;
		case 'D' :etat_courant=TEST_UART_DMA; 		break;
		case 'c' :etat_courant=MENU_START_PRINT; 	break;
	}

}


void print_menu_timer(){
	PRINTF("\r\n***** Test de l'UART 2 ***** Touche 'c' pour sortir\r\n");
	PRINTF("\t(B) Basic Timer TIM6\r\n");
	PRINTF("\t(I) Input Capture TIM3\r\n");

	/***** Test sortie du menu *****/
	do{
		while(ready!=1);
		ready=0;
	}
	while(rx_buffer_uart[0]!='I' && rx_buffer_uart[0]!='B' && rx_buffer_uart[0]!='c');

	switch(rx_buffer_uart[0]){
		case 'B' :etat_courant=TEST_BASIC_TIM6;				break;
		case 'I' :etat_courant=TEST_INPUT_CAPTURE_TIM3; 	break;
		case 'c' :etat_courant=MENU_START_PRINT; 			break;
	}

}


void VirtualCOM_Transmit( char *format, ... ){
	char buffer[128];
	va_list args;
	va_start(args, format);

	BACKUP_PRIMASK();	// Sauvegarde valeur "IT Enable"
	DISABLE_IRQ();		// Reset  "IT Enable"
	vsprintf(buffer,format,args);
	HAL_UART_Transmit(&huart2,buffer,strlen(buffer),200);
	RESTORE_PRIMASK();	// Restore la valeur sauvegardée de "IT Enable"
  	va_end(args);
}

