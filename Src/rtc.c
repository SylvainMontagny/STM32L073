/*
 * rtc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */

#include "rtc.h"


void test_rtc(state etat){
	uint32_t sortir_etat=0,temp=0;
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	char jour_str[3], mois_str[3], annee_str[3];
	char heure_str[3], minute_str[3], seconde_str[3];
	uint32_t jour, mois, annee;
	uint32_t heure, minute, seconde;
	char *tail_ptr;

	switch (etat){
		case TEST_RTC_GET :
			sortir_etat=0;
			while(sortir_etat==0){
				/***** R�cup�ration Time et Date *****/
				HAL_RTC_GetTime(&hrtc,&my_time,RTC_FORMAT_BIN);
				HAL_RTC_GetDate(&hrtc,&my_date,RTC_FORMAT_BIN);
				/***** Affichage Time et Date *****/
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"Date : %02u/%02u/%02u \t\t Time : %02u:%02u:%02u                   \r", my_date.Date,my_date.Month,my_date.Year,my_time.Hours,my_time.Minutes,my_time.Seconds);
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
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
			snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\n");
			HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);

			break;

		case TEST_RTC_SET :
			sortir_etat=0;
			while(sortir_etat==0){
				/***** Enregistrement de Date *****/
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nSaisir la date au format xx/xx/xx\r\n");
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
				while(ready==0);
				ready=0;
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
						(sDate.Year<0)		||	(sDate.Year>19) ||
						(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN)!=HAL_OK)){
					snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nErreur de saisie\r\n",temp);
					HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
				}
				else {
					sortir_etat=1;
					snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nDate enregistr�e dans la RTC\r\n",temp);
					HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
					}
			}


			sortir_etat=0;
			while(sortir_etat==0){
				/***** Enregistrement de l'heure *****/
				snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nSaisir l'heure au format xx:xx:xx\r\n");
				HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
				while(ready==0);
				ready=0;
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
					snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nErreur de saisie\r\n",temp);
					HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
				}
				else {
					sortir_etat=1;
					snprintf(tx_buffer_uart,TAILLE_BUF_UART_TX,"\r\nHeure enregistr�e dans la RTC\r\n",temp);
					HAL_UART_Transmit(&huart2,tx_buffer_uart,strlen(tx_buffer_uart),1000);
					}
			}
			break;

		case TEST_RTC_ALARM:
			/****** Activation des IRQ de la RTC *****/
			HAL_NVIC_EnableIRQ(RTC_IRQn);
			/***** Test sortie du menu *****/
			do{
				while(ready!=1);
				ready=0;
			}
			while(rx_buffer_uart[0]!='c');
			/***** Desactivation des IRQ de la RTC *****/
			HAL_NVIC_DisableIRQ(RTC_IRQn);
			__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc,RTC_FLAG_ALRAF);
			break;

		default:
			break;
	}
}
