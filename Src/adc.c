/*
 * adc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#include "adc.h"

void test_adc(state etat){
	uint32_t sortir_etat=0;
	uint16_t value_IN0, value_TEMP, value_CALIB,value_DAC=0;
	uint16_t tab_value_DAC[]={0,500,1000,1500,2000,2500,3000,3500,4000,4095};
	int32_t temperature;
	uint32_t i;
	float tension;

	switch(etat){
		case TEST_ADC_IN0 :
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"ADC : Lecture analogique sur IN0 : PA0 (A0 Nucléo)\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"DAC : Génération analogique sur DAC_OUT : PA4 (A2 Nucléo)\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Press enter to Start\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Then Press enter to Hold one acquisition\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			while(ready!=1);	//Press Enter
			ready=0;

			while(sortir_etat==0){
				/***** Gestion du DAC *****/
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,value_DAC);
				HAL_Delay(4);
				value_DAC=(value_DAC+20)%4096;
				/***** Gestion de l'ADC *****/
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
				value_IN0=HAL_ADC_GetValue(&hadc);
				/***** Calcul et affichage de la valeur convertie *****/
				tension=value_IN0*3.3/4096;
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Tension : %5.3f Volt \t ADC[%4u] \t\t                  \r", tension, value_IN0);
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
				HAL_Delay(100);
				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
			/***** Sortie du menu *****/
			HAL_ADC_Stop(&hadc);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			break;

		case TEST_ADC_TEMPERATURE :
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"ADC : Lecture IN0 et Lecture Temperature Sensor (Internal)\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);

			while(sortir_etat==0){
				/***** Gestion du DAC *****/
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,value_DAC);
				HAL_Delay(4);
				value_DAC=(value_DAC+500)%4096;
				/***** Gestion de l'ADC *****/
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,1000);
				value_IN0=HAL_ADC_GetValue(&hadc);
				HAL_ADC_PollForConversion(&hadc,1000);
				value_TEMP=HAL_ADC_GetValue(&hadc);
				/***** Calcul et Afficage des valeurs converties *****/
				tension=value_IN0*3.3/4096;
				temperature = ( (130-30) * (value_TEMP - *TS_CAL1_ADDR) / (*TS_CAL2_ADDR - *TS_CAL1_ADDR) ) + 30;
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Temperature :\t%5d °C\tADC[%4u]                   \n\r", temperature, value_TEMP);
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Tension :\t%5.3f Volt\tADC[%4u]                   \n\r\r\n", tension,  value_IN0);
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
				HAL_Delay(3000);
				/***** Test Sortie du menu *****/
				if(ready==1){
					ready=0;
					if(rx_buffer_uart[0]=='c'){
						sortir_etat=1;
					}
				}
			}
			/***** Sortie du menu *****/
			HAL_ADC_Stop(&hadc);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			break;


		case TEST_ADC_CALIB :
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Conversion AVANT Calibration\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			/***** Conversion SANS Calibration *****/
			for(i=0;i<10;i++){
						HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
						HAL_Delay(4);
						HAL_ADC_Start(&hadc);
						HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
						value_IN0=HAL_ADC_GetValue(&hadc);
						snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN0,(int32_t)tab_value_DAC[i]-(int32_t)value_IN0, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN0)*3300.0/4096);
						HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
						HAL_ADC_Stop(&hadc);
			}
			/***** Conversion APRES Calibration *****/
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nConversion APRES Calibration\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
			HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
			value_CALIB=HAL_ADCEx_Calibration_GetValue(&hadc,ADC_SINGLE_ENDED);
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Calibrating process...... valeur : %u \r\n", value_CALIB);
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
			for(i=0;i<10;i++){
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
				HAL_Delay(4);
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
				value_IN0=HAL_ADC_GetValue(&hadc);
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN0,(int32_t)tab_value_DAC[i]-(int32_t)value_IN0, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN0)*3300.0/4096);
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),HAL_MAX_DELAY);
				HAL_ADC_Stop(&hadc);
			}
			break;

		default:
			break;
	}

}

