/*
 * rtc.c
 *
 *  Created on: 17 nov. 2017
 *      Author: Sylvain
 */


#include "stm32l0xx_hal.h"
#include "main.h"
#include "rtc.h"


void test_rtc(state mode);

extern uint8_t msg[TAILLE_BUF];
extern UART_HandleTypeDef huart2;
extern uint8_t rx_buffer[TAILLE_BUF];
extern uint8_t ready;
extern RTC_HandleTypeDef hrtc;
extern RTC_DateTypeDef my_date;
extern RTC_TimeTypeDef my_time;




void test_rtc(state mode){

	uint32_t sortir_etat=0;
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	char jour_str[3];
	char mois_str[3];
	char annee_str[3];
	char heure_str[3];
	char minute_str[3];
	char seconde_str[3];
	uint32_t jour, mois, annee;
	uint32_t heure, minute, seconde;
	char *tail_ptr;
	uint32_t temp=0;

	switch (mode){
		case TEST_RTC_GET :
			sortir_etat=0;
			while(sortir_etat==0){
			HAL_RTC_GetTime(&hrtc,&my_time,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,&my_date,RTC_FORMAT_BIN);
			snprintf(msg,TAILLE_BUF,"Date : %02u/%02u/%02u \t\t Time : %02u:%02u:%02u                   \r", my_date.Date,my_date.Month,my_date.Year,my_time.Hours,my_time.Minutes,my_time.Seconds);
			HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
			HAL_Delay(100);

			if(	(ready==1) && (rx_buffer[0]=='c')	){
						sortir_etat=1;
						snprintf(msg,TAILLE_BUF,"\r\n");
						HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					}
					else{
						ready=0;		// mais on reste dans le mode rtc_test
					}
			}
			ready=0;
			break;

		case TEST_RTC_SET :
			sortir_etat=0;
			while(sortir_etat==0){
				/***** Enregistrement de la date *****/
				snprintf(msg,TAILLE_BUF,"\r\nSaisir la date au format xx/xx/xx\r\n");
				HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
				while(ready==0);
				ready=0;
				jour_str[0]=rx_buffer[0];
				jour_str[1]=rx_buffer[1];
				sDate.Date=strtol(jour_str, &tail_ptr,10);
				mois_str[0]=rx_buffer[3];
				mois_str[1]=rx_buffer[4];
				sDate.Month= strtol(mois_str, &tail_ptr,10);
				annee_str[0]=rx_buffer[6];
				annee_str[1]=rx_buffer[7];
				sDate.Year= strtol(annee_str, &tail_ptr,10);
				if( 	(sDate.Date<=0)		|| 	(sDate.Date>31)	||
						(sDate.Month<=0)	||	(sDate.Month>12)||
						(sDate.Year<0)		||	(sDate.Year>19) ||
						(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN)!=HAL_OK)){
					snprintf(msg,TAILLE_BUF,"\r\nErreur de saisie\r\n",temp);
					HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
				}
				else {
					sortir_etat=1;
					snprintf(msg,TAILLE_BUF,"\r\nDate enregistrée dans la RTC\r\n",temp);
					HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					}
			}

			/***** Enregistrement de l'heure *****/
			sortir_etat=0;
				while(sortir_etat==0){
					/***** Enregistrement de la date *****/
					snprintf(msg,TAILLE_BUF,"\r\nSaisir l'heure au format xx:xx:xx\r\n");
					HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					while(ready==0);
					ready=0;
					heure_str[0]=rx_buffer[0];
					heure_str[1]=rx_buffer[1];
					sTime.Hours=strtol(heure_str, &tail_ptr,10);
					minute_str[0]=rx_buffer[3];
					minute_str[1]=rx_buffer[4];
					sTime.Minutes= strtol(minute_str, &tail_ptr,10);
					seconde_str[0]=rx_buffer[6];
					seconde_str[1]=rx_buffer[7];
					sTime.Seconds= strtol(seconde_str, &tail_ptr,10);
					if( 	(sTime.Hours<0)		|| 	(sTime.Hours>23)	||
							(sTime.Minutes<0)	||	(sTime.Minutes>59)	||
							(sTime.Seconds<0)	||	(sTime.Seconds>59) 	||
							(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN)!=HAL_OK)){
						snprintf(msg,TAILLE_BUF,"\r\nErreur de saisie\r\n",temp);
						HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
					}
					else {
						sortir_etat=1;
						snprintf(msg,TAILLE_BUF,"\r\nHeure enregistrée dans la RTC\r\n",temp);
						HAL_UART_Transmit(&huart2,msg,strlen(msg),1000);
						}
				}
			break;

		case TEST_RTC_ALARM:
			HAL_NVIC_EnableIRQ(RTC_IRQn);
			do{
					while(ready!=1);
					ready=0;
				}
				while(rx_buffer[0]!='c');
			HAL_NVIC_DisableIRQ(RTC_IRQn);
			__HAL_RTC_ALARM_CLEAR_FLAG(&hrtc,RTC_FLAG_ALRAF);
			break;
	}




}
