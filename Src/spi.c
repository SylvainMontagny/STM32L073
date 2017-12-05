/*
 * spi.c
 *
 *  Created on: 5 déc. 2017
 *      Author: Sylvain
 */

#include "spi.h"


void test_spi(void){
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n***** SPI (DMA) *****\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Relier MOSI(PC3) et MISO (PC2)\r\n\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);

	/***** Buffer RX et TX AVANT transmission *****/
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Buffer RX et TX avant transmission :\r\n");
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"TX : %2u %2u %2u %2u %2u %2u %2u %2u %2u %2u\r\n", tx_buffer_spi[0],tx_buffer_spi[1],tx_buffer_spi[2],tx_buffer_spi[3],tx_buffer_spi[4],tx_buffer_spi[5],tx_buffer_spi[6],tx_buffer_spi[7],tx_buffer_spi[8],tx_buffer_spi[9]);
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
	snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"RX : %2u %2u %2u %2u %2u %2u %2u %2u %2u %2u\r\n", rx_buffer_spi[0],rx_buffer_spi[1],rx_buffer_spi[2],rx_buffer_spi[3],rx_buffer_spi[4],rx_buffer_spi[5],rx_buffer_spi[6],rx_buffer_spi[7],rx_buffer_spi[8],rx_buffer_spi[9]);
	HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);

	/***** Transmission ET Reception SPI en mode DMA *****/
	HAL_SPI_TransmitReceive_DMA(&hspi2,(uint8_t*)tx_buffer_spi,(uint8_t*)rx_buffer_spi,10);

	/***** Sortie du menu *****/
	HAL_Delay(20);				// Permet de laisser le temps au callback d'afficher tout le texte.
}

