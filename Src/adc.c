/*
 * adc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#include "adc.h"

void test_adc(state etat){
	uint32_t sortir_etat=0;
	uint16_t value_IN1, value_TEMP, value_CALIB,value_DAC=0;
	uint16_t tab_value_DAC[]={0,500,1000,1500,2000,2500,3000,3500,4000,4095};
	int32_t temperature;
	uint32_t i;
	float tension;

	switch(etat){
		case TEST_ADC_IN1 :
			PRINTF("ADC : Lecture analogique channel IN1\r\n");
			PRINTF("Relier DAC_OUT [PA4 / A2] à IN1 [PA1 / A1] \r\n");
			PRINTF("Press enter to Start\r\n");
			PRINTF("Then Press enter to Hold one acquisition\r\n");
			
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
				value_IN1=HAL_ADC_GetValue(&hadc);
				/***** Calcul et affichage de la valeur convertie *****/
				tension=value_IN1*3.3/4096;
				PRINTF("Tension : %5.3f Volt \t ADC[%4u] \t\t                  \r", tension, value_IN1);
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
			PRINTF("\r\n");
			
			break;

		case TEST_ADC_TEMPERATURE :
			PRINTF("ADC : Lecture IN1 et Lecture Temperature Sensor (Internal)\r\n");
			

			while(sortir_etat==0){
				/***** Gestion du DAC *****/
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,value_DAC);
				HAL_Delay(4);
				value_DAC=(value_DAC+500)%4096;
				/***** Gestion de l'ADC *****/
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,1000);
				value_IN1=HAL_ADC_GetValue(&hadc);
				HAL_ADC_PollForConversion(&hadc,1000);
				value_TEMP=HAL_ADC_GetValue(&hadc);
				/***** Calcul et Afficage des valeurs converties *****/
				tension=value_IN1*3.3/4096;
				temperature = ( (130-30) * (value_TEMP - *TS_CAL1_ADDR) / (*TS_CAL2_ADDR - *TS_CAL1_ADDR) ) + 30;
				PRINTF("Temperature :\t%5d °C\tADC[%4u]                   \n\r", temperature, value_TEMP);
				PRINTF("Tension :\t%5.3f Volt\tADC[%4u]                   \n\r\r\n", tension,  value_IN1);
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
			PRINTF("\r\n");
			break;

		case TEST_ADC_CALIB :
			PRINTF("Conversion AVANT Calibration\r\n");
			/***** Conversion SANS Calibration *****/
			for(i=0;i<10;i++){
						HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
						HAL_Delay(4);
						HAL_ADC_Start(&hadc);
						HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
						value_IN1=HAL_ADC_GetValue(&hadc);
						PRINTF("DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN1,(int32_t)tab_value_DAC[i]-(int32_t)value_IN1, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN1)*3300.0/4096);
						HAL_ADC_Stop(&hadc);
			}
			/***** Conversion APRES Calibration *****/
			PRINTF("\r\nConversion APRES Calibration\r\n");
			HAL_ADCEx_Calibration_Start(&hadc,ADC_SINGLE_ENDED);
			value_CALIB=HAL_ADCEx_Calibration_GetValue(&hadc,ADC_SINGLE_ENDED);
			PRINTF("Calibrating process...... valeur : %u \r\n", value_CALIB);
			for(i=0;i<10;i++){
				HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,tab_value_DAC[i]);
				HAL_Delay(4);
				HAL_ADC_Start(&hadc);
				HAL_ADC_PollForConversion(&hadc,HAL_MAX_DELAY);
				value_IN1=HAL_ADC_GetValue(&hadc);
				PRINTF("DAC[%4u]\tADC[%4u]\tDAC-ADC[%4d][%6.1f mV]   \t\t\t\t  \r\n",tab_value_DAC[i],value_IN1,(int32_t)tab_value_DAC[i]-(int32_t)value_IN1, ((int32_t)tab_value_DAC[i]-(int32_t)value_IN1)*3300.0/4096);
				HAL_ADC_Stop(&hadc);
			}
			break;

		default:
			break;
	}

}

