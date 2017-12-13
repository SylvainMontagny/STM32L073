/*
 * uart.c
 *
 *  Created on: 11 déc. 2017
 *      Author: Sylvain
 */

#include "uart.h"

void test_uart(state etat){

	uint32_t sortir_etat=0;

	switch(etat){
		case TEST_UART_POLLING :
			HAL_UART_Init(&hlpuart1);
			HAL_NVIC_DisableIRQ(AES_RNG_LPUART1_IRQn);
			PRINTF("Mode Scrutation : Envoi/Reception d'un caractère\r\n");
			PRINTF("Relier TX_LPUART1 [PC1] à RX_LP_UART1 [PC0]\r\n");
			while(sortir_etat==0){
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,1,100);
				HAL_UART_Receive(&hlpuart1,rx_buffer_lpuart,1,100);

				HAL_UART_Transmit(&huart2,rx_buffer_lpuart,1,100);
				HAL_Delay(1000);
				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
			HAL_UART_DeInit(&hlpuart1);
		break;


		case TEST_UART_IT :
			HAL_UART_Init(&hlpuart1);
			PRINTF("\r\nMode IT : Envoi / Reception de 5 caractères\r\n");
			PRINTF("Relier TX_LPUART1 [PC1] à RX_LP_UART1 [PC0]\r\n\r\n");
			/***** Attente de 4 caractères en INTERRUPTION ****/
			HAL_UART_Receive_IT(&hlpuart1,rx_buffer_lpuart,4);

			while(sortir_etat==0){
				/***** Transmission de 4 caractères en POLLING *****/
				PRINTF("\r\nLP_UART Transmit (POLLING): \t%s",tx_buffer_lpuart);
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,4,100);

				/***** Attente INTERRUPTION ****/
				while(lpuart_IT_Received==0);
				lpuart_IT_Received=0;

				/***** Attente de 4 nouveaux caractères en INTERRUPTION ****/
				HAL_UART_Receive_IT(&hlpuart1,rx_buffer_lpuart,4);
				HAL_Delay(3000);


				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
			HAL_UART_DeInit(&hlpuart1);
		break;

		case TEST_UART_DMA :
			HAL_UART_Init(&hlpuart1);
			PRINTF("\r\nMode IT : Envoi / Reception de 5 caractères\r\n");
			PRINTF("Relier TX_LPUART1 [PC1] à RX_LP_UART1 [PC0]\r\n\r\n");
			/***** Attente de 4 caractères en INTERRUPTION DMA****/
			HAL_UART_Receive_DMA(&hlpuart1,rx_buffer_lpuart,4);

			while(sortir_etat==0){
				/***** Transmission de 4 caractères en POLLING *****/
				PRINTF("\r\nLP_UART Transmit (POLLING): \t%s",tx_buffer_lpuart);
				HAL_UART_Transmit(&hlpuart1,tx_buffer_lpuart,4,100);

				/***** Attente INTERRUPTION ****/
				while(lpuart_DMA_Received==0);
				lpuart_DMA_Received=0;

				/***** Attente de 4 nouveaux caractères en INTERRUPTION ****/
				HAL_UART_Receive_DMA(&hlpuart1,rx_buffer_lpuart,4);
				HAL_Delay(3000);


				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
			HAL_UART_DeInit(&hlpuart1);
		break;

	}

}
