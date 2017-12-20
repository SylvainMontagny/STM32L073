/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* MACRO */
#define PRINTF(...)			VirtualCOM_Transmit(__VA_ARGS__)
#define BACKUP_PRIMASK()  	uint32_t primask_bit= __get_PRIMASK()
#define DISABLE_IRQ() 		__disable_irq()
#define ENABLE_IRQ() 		__enable_irq()
#define RESTORE_PRIMASK()	 __set_PRIMASK(primask_bit)
#define START_MESURE		GPIOA->BSRR = GPIO_PIN_11
#define STOP_MESURE			GPIOA->BRR = GPIO_PIN_11

/***** Escape Caracters *****/
#define TERMINAL_RESET		"\033[0m"			// Reset all attribute
#define CURSOR_TOP_LEFT		"\033[0;0H"			// Cursor back to Top-Left
#define CLEAR_SCREEN		"\033[0;0H\033[2J"	// Clear Screen
#define BLACK				"\033[30m" 			// Black
#define RED					"\033[31m"			// Red
#define GREEN				"\033[32m"			// Green


/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define MESURE_Pin GPIO_PIN_11
#define MESURE_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/***** Taille du buffer d'émmission pour USART2 TX *****/
#define TAILLE_BUF_UART_RX	 	100
#define TAILLE_BUF_UART_TX	 	100
#define TAILLE_BUF_LPUART_RX	10
#define TAILLE_BUF_LPUART_TX	10
#define TAILLE_BUF_SPI		 	10

/***** Machine d'état du projet *****/
typedef enum {	MENU_START_PRINT,
				MENU_GPIO_PRINT,
				TEST_GPIO_POLLING,
				TEST_GPIO_IT,
				MENU_ADC_PRINT,
				TEST_ADC_TEMPERATURE,
				TEST_ADC_IN1,
				TEST_ADC_CALIB,
				MENU_RTC_PRINT,
				TEST_RTC_GET,
				TEST_RTC_SET,
				TEST_RTC_ALARM,
				MENU_TIMER_PRINT,
				TEST_TIM6_BASIC,
				TEST_TIM3_IC_PA5,
				TEST_TIM3_IC_PA11,
				TEST_SPI,
				MENU_UART_PRINT,
				TEST_UART_POLLING,
				TEST_UART_IT,
				TEST_UART_DMA
}state;

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
