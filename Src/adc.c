/*
 * adc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#include "adc.h"
#include "stm32l0xx_hal.h"
#include "main.h"


#define TS_CAL1_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007A))
#define TS_CAL2_ADDR  ((uint16_t*) ((uint32_t) 0x1FF8007E))

void test_adc(state mode);

extern uint8_t msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc;
DAC_HandleTypeDef hdac;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;


void test_adc(state mode){
	uint32_t sortir_etat=0;
	uint16_t value_IN0, value_TEMP, value_CALIB,value_DAC;
	uint16_t tab_value_DAC[]={0,500,1000,1500,2000,2500,3000,3500,4000,4095};
	int32_t temperature;
	uint32_t i;
	float tension;

	switch(mode){
		case TEST_ADC_IN0 :
			snprintf(msg,TAILLE_BUF,"ADC : Lecture analogique sur IN0 : PA0 (A0 Nucl�o)\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			snprintf(msg,TAILLE_BUF,"DAC : G�n�ration analogique sur DAC_OUT : PA4 (A2 Nucl�o)\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			snprintf(msg,TAILLE_BUF,"Press enter to Start\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			snprintf(msg,TAILLE_BUF,"Then Press enter to Hold one acquisition\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			while(ready!=1);	//Press Enter
			ready=0;


			while(sortir_etat==0){
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,value_DAC);
				HAL_Delay(4);
				//i=2048;
				value_DAC=(value_DAC+10)%4096;
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
				value_IN0=HAL_ADC_GetValue(&hadc);
				tension=value_IN0*3.3/4096;
				snprintf(msg,TAILLE_BUF,"Valeur ADC : \t%u \t\tTension : \t%.3f Volt                   \r", value_IN0, tension);
				HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
				HAL_Delay(50);
				if(	(ready==1) && (rx_buffer[0]=='c')	){
					sortir_etat=1;
					snprintf(msg,TAILLE_BUF,"\r\n");
					HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					HAL_ADC_Stop(&hadc);
				}
				else{
					ready=0;		// mais on reste dans le mode GPIO_POLLING
				}
			}
			ready=0;
			break;

		case TEST_ADC_TEMPERATURE :
			snprintf(msg,TAILLE_BUF,"ADC : Lecture IN0 et Lecture Temperature Sensor (Internal)\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			// Sampling time is set to 160.5 for the temperature sensor (see datasheet)

			while(sortir_etat==0){

				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,value_DAC);
				HAL_Delay(4);
				value_DAC=(value_DAC+500)%4096;

				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,1000);
				value_IN0=HAL_ADC_GetValue(&hadc);

				//HAL_ADC_Start(&hadc);			// A mettre si fonctionnement en Discontinous
				HAL_ADC_PollForConversion(&hadc,1000);
				value_TEMP=HAL_ADC_GetValue(&hadc);

				tension=value_IN0*3.3/4096;
				//temperature=130-30 /CAL2-CAL1 (DATA - CAL1) + 30�C
				temperature = ( (130-30) * (value_TEMP - *TS_CAL1_ADDR) / (*TS_CAL2_ADDR - *TS_CAL1_ADDR) ) + 30;
				snprintf(msg,TAILLE_BUF,"Temperature :\t%5d �C\t[%4u]                   \n\r", temperature, value_TEMP);
				HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
				snprintf(msg,TAILLE_BUF,"Tension :\t%5.3f Volt\t[%4u]                   \n\r\r\n", tension,  value_IN0);
				HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);

				HAL_Delay(3000);
				if(	(ready==1) && (rx_buffer[0]=='c')	){
					sortir_etat=1;
					snprintf(msg,TAILLE_BUF,"\r\n");
					HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					HAL_ADC_Stop(&hadc);
				}
				else{
					ready=0;		// mais on reste dans le mode GPIO_POLLING
				}
			}
			ready=0;
			break;


		case TEST_ADC_CALIB :
			snprintf(msg,TAILLE_BUF,"Conversion AVANT Calibration\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			//HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
			//value_CALIB=HAL_ADCEx_Calibration_GetValue(&hadc,ADC_SINGLE_ENDED);


			for(i=0;i<10;i++){
						HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
						HAL_Delay(4);
						HAL_ADC_Start(&hadc);
						HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
						value_IN0=HAL_ADC_GetValue(&hadc);
						snprintf(msg,TAILLE_BUF,"DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN0,(int32_t)tab_value_DAC[i]-(int32_t)value_IN0, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN0)*3300.0/4096);
						HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
						HAL_ADC_Stop(&hadc);
			}

			snprintf(msg,TAILLE_BUF,"\r\nConversion APRES Calibration\r\n");
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
			value_CALIB=HAL_ADCEx_Calibration_GetValue(&hadc,ADC_SINGLE_ENDED);
			snprintf(msg,TAILLE_BUF,"Calibrating process...... valeur : %u \r\n", value_CALIB);
			HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
			for(i=0;i<10;i++){
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
				HAL_Delay(4);
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
				value_IN0=HAL_ADC_GetValue(&hadc);
				snprintf(msg,TAILLE_BUF,"DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN0,(int32_t)tab_value_DAC[i]-(int32_t)value_IN0, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN0)*3300.0/4096);
				HAL_UART_Transmit(&huart2,msg,strlen(msg),HAL_MAX_DELAY);
				HAL_ADC_Stop(&hadc);
			}

			break;
	}

}

