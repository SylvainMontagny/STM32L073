/*
 * uart.c
 *
 *  Created on: 11 d�c. 2017
 *      Author: Sylvain
 */

#include "uart.h"

void test_uart(state etat){


	switch(etat){
		case TEST_UART_POLLING :
			HAL_UART_Init(&hlpuart1);
			HAL_NVIC_DisableIRQ(AES_RNG_LPUART1_IRQn);
			PRINTF(RED);
			PRINTF("Mode Scrutation : Envoi/Reception d'un caractere\r\n");
			PRINTF("Connect TX_LPUART1 [PC1] with RX_LP_UART1 [PC0]\r\n");
			PRINTF(BLACK);

			SortieEtat=0;
			while(SortieEtat==0){
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,1,100);
				HAL_UART_Receive(&hlpuart1,rx_buffer_lpuart,1,100);

				HAL_UART_Transmit(&huart2,rx_buffer_lpuart,1,100);
				HAL_Delay(1000);
				/***** Test Sortie du menu *****/
				AttenteSortieEtat=1;
			}
			AttenteSortieEtat=0;
			HAL_UART_DeInit(&hlpuart1);
		break;


		case TEST_UART_IT :
			HAL_UART_Init(&hlpuart1);
			PRINTF(RED);
			PRINTF("\r\nMode IT : Envoi / Reception de 5 caracteres\r\n");
			PRINTF("Connect TX_LPUART1 [PC1]  with RX_LP_UART1 [PC0]\r\n\r\n");
			PRINTF(BLACK);
			/***** Attente de 4 caracteres en INTERRUPTION ****/
			HAL_UART_Receive_IT(&hlpuart1,rx_buffer_lpuart,4);

			SortieEtat=0;
			while(SortieEtat==0){
				/***** Transmission de 4 caracteres en POLLING *****/
				PRINTF("\r\nLP_UART Transmit (POLLING): \t%s",tx_buffer_lpuart);
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,4,100);

				/***** Attente INTERRUPTION ****/
				while(LPUART_IsITReceived==0);
				LPUART_IsITReceived=0;

				/***** Attente de 4 nouveaux caracteres en INTERRUPTION ****/
				HAL_UART_Receive_IT(&hlpuart1,rx_buffer_lpuart,4);
				HAL_Delay(3000);


				/***** Test Sortie du menu *****/
				AttenteSortieEtat=1;
			}
			AttenteSortieEtat=0;
			HAL_UART_DeInit(&hlpuart1);
		break;

		case TEST_UART_DMA :
			HAL_UART_Init(&hlpuart1);
			PRINTF(RED);
			PRINTF("\r\nMode IT : Envoi / Reception de 5 caracteres\r\n");
			PRINTF("Connect TX_LPUART1 [PC1]  with  RX_LP_UART1 [PC0]\r\n\r\n");
			PRINTF(BLACK);
			/***** Attente de 4 caracteres en INTERRUPTION DMA****/
			HAL_UART_Receive_DMA(&hlpuart1,rx_buffer_lpuart,4);
			SortieEtat=0;
			while(SortieEtat==0){
				/***** Transmission de 4 caracteres en POLLING *****/
				PRINTF("\r\nLP_UART Transmit (POLLING): \t%s",tx_buffer_lpuart);
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,4,100);

				/***** Attente INTERRUPTION ****/
				while(LPUART_IsDMAReceived==0);
				LPUART_IsDMAReceived=0;

				/***** Attente de 4 nouveaux caracteres en INTERRUPTION ****/
				HAL_UART_Receive_DMA(&hlpuart1,rx_buffer_lpuart,4);
				HAL_Delay(3000);


				/***** Test Sortie du menu *****/
				AttenteSortieEtat=1;
			}
			AttenteSortieEtat=0;
			HAL_UART_DeInit(&hlpuart1);
		break;

	}

}
