/*
 * spi.c
 *
 *  Created on: 5 d�c. 2017
 *      Author: Sylvain
 */

#include "spi.h"


void test_spi(void){
	uint8_t SpiTransmitValide=1;
	uint32_t i;

	PRINTF(CLEAR_SCREEN);
	PRINTF(RED);
	PRINTF("\r\n***** SPI (DMA) *****\r\n");
	PRINTF("Connect MOSI(PC3) with MISO (PC2)\r\n\r\n");
	PRINTF(BLACK);
	/***** Buffer RX et TX AVANT transmission *****/
	PRINTF("Buffer RX et TX avant transmission :\r\n");
	PRINTF("+------------------------------------------------------+\r\n");
	PRINTF("| TX | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u |\r\n", tx_buffer_spi[0],tx_buffer_spi[1],tx_buffer_spi[2],tx_buffer_spi[3],tx_buffer_spi[4],tx_buffer_spi[5],tx_buffer_spi[6],tx_buffer_spi[7],tx_buffer_spi[8],tx_buffer_spi[9]);
	PRINTF("+------------------------------------------------------+\r\n");
	PRINTF("| RX | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u | %2u |\r\n", rx_buffer_spi[0],rx_buffer_spi[1],rx_buffer_spi[2],rx_buffer_spi[3],rx_buffer_spi[4],rx_buffer_spi[5],rx_buffer_spi[6],rx_buffer_spi[7],rx_buffer_spi[8],rx_buffer_spi[9]);
	PRINTF("+------------------------------------------------------+\r\n");
	/***** Transmission ET Reception SPI en mode DMA *****/
	HAL_SPI_TransmitReceive_DMA(&hspi2,(uint8_t*)tx_buffer_spi,(uint8_t*)rx_buffer_spi,10);

	/***** Sortie du menu *****/
	HAL_Delay(20);				// Permet de laisser le temps au callback d'afficher tout le texte.
	for(i=0;i<10;i++){
		if(rx_buffer_spi[i]!=tx_buffer_spi[i]){
			SpiTransmitValide=0;
		}
	}
	if(SpiTransmitValide==1){
		PRINTF("\r\nTransmission SPI OK !!!\r\n");
	}
	else{
		PRINTF("\r\nTransmission SPI Failed !\r\n");
	}
	SortieEtat=0;
	AttenteSortieEtat=1;
	while(SortieEtat==0);
	AttenteSortieEtat=0;
}

