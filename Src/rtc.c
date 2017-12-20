/*
 * rtc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#include "rtc.h"


void test_rtc(state etat){
	uint8_t DateValide=0, HeureValide=0;
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	char jour_str[3], mois_str[3], annee_str[3];
	char heure_str[3], minute_str[3], seconde_str[3];

	char *tail_ptr;

	switch (etat){
		case TEST_RTC_GET :
			SortieEtat=0;
			while(SortieEtat==0){
				/***** Récupération Time et Date *****/
				HAL_RTC_GetTime(&hrtc,&my_time,RTC_FORMAT_BIN);
				HAL_RTC_GetDate(&hrtc,&my_date,RTC_FORMAT_BIN);
				/***** Affichage Time et Date *****/
				PRINTF("Date : %02u/%02u/%02u \t\t Time : %02u:%02u:%02u                   \r", my_date.Date,my_date.Month,my_date.Year,my_time.Hours,my_time.Minutes,my_time.Seconds);
				HAL_Delay(100);
				/***** Test Sortie du menu *****/
				AttenteSortieEtat=1;
			}
			/***** Sortie du menu *****/
			AttenteSortieEtat=0;
			PRINTF("\r\n");
			break;

		case TEST_RTC_SET :
			DateValide=0;
			while(DateValide==0){
				/***** Enregistrement de Date *****/
				PRINTF("\r\nSaisir la date au format xx/xx/xx\r\n");
				while(UART2_IsStringValid==0);
				UART2_IsStringValid=0;
				jour_str[0]=rx_buffer_uart[0];
				jour_str[1]=rx_buffer_uart[1];
				sDate.Date=strtol(jour_str, &tail_ptr,10);
				mois_str[0]=rx_buffer_uart[3];
				mois_str[1]=rx_buffer_uart[4];
				sDate.Month= strtol(mois_str, &tail_ptr,10);
				annee_str[0]=rx_buffer_uart[6];
				annee_str[1]=rx_buffer_uart[7];
				sDate.Year= strtol(annee_str, &tail_ptr,10);
				if( 	(sDate.Date<=0)		|| 	(sDate.Date>31)	||
						(sDate.Month<=0)	||	(sDate.Month>12)||
						(sDate.Year<0)		||	(sDate.Year>99) ||
						(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN)!=HAL_OK)){
					PRINTF("\r\nErreur de saisie\r\n");
				}
				else {
					DateValide=1;
					PRINTF("Date enregistrée dans la RTC\r\n");
					}
			}

			HeureValide=0;
			while(HeureValide==0){
				/***** Enregistrement de l'heure *****/
				PRINTF("\r\nSaisir l'heure au format xx:xx:xx\r\n");
				while(UART2_IsStringValid==0);
				UART2_IsStringValid=0;
				heure_str[0]=rx_buffer_uart[0];
				heure_str[1]=rx_buffer_uart[1];
				sTime.Hours=strtol(heure_str, &tail_ptr,10);
				minute_str[0]=rx_buffer_uart[3];
				minute_str[1]=rx_buffer_uart[4];
				sTime.Minutes= strtol(minute_str, &tail_ptr,10);
				seconde_str[0]=rx_buffer_uart[6];
				seconde_str[1]=rx_buffer_uart[7];
				sTime.Seconds= strtol(seconde_str, &tail_ptr,10);
				if( 	(sTime.Hours<0)		|| 	(sTime.Hours>23)	||
						(sTime.Minutes<0)	||	(sTime.Minutes>59)	||
						(sTime.Seconds<0)	||	(sTime.Seconds>59) 	||
						(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN)!=HAL_OK)){
					PRINTF("\r\nErreur de saisie\r\n");
				}
				else {
					HeureValide=1;
					PRINTF("Heure enregistrée dans la RTC\r\n");
					}
			}

			/***** Sortie du menu *****/
			SortieEtat=0;
			AttenteSortieEtat=1;
			while(SortieEtat==0);
			AttenteSortieEtat=0;
			break;

		case TEST_RTC_ALARM:
			/****** Activation des IRQ de la RTC *****/
			HAL_NVIC_EnableIRQ(RTC_IRQn);
			/***** Test sortie du menu *****/
			SortieEtat=0;
			AttenteSortieEtat=1;
			while(SortieEtat==0);
			AttenteSortieEtat=0;
			/***** Desactivation des IRQ de la RTC *****/
			HAL_NVIC_DisableIRQ(RTC_IRQn);
			__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc,RTC_FLAG_ALRAF);
			break;

		default:
			break;
	}
}
