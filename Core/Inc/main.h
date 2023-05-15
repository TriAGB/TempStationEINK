/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DISP_BUSY_Pin GPIO_PIN_15
#define DISP_BUSY_GPIO_Port GPIOC
#define CLOCK_INT_Pin GPIO_PIN_0
#define CLOCK_INT_GPIO_Port GPIOA
#define LIGHT_Pin GPIO_PIN_1
#define LIGHT_GPIO_Port GPIOA
#define DISP_RESET_Pin GPIO_PIN_2
#define DISP_RESET_GPIO_Port GPIOA
#define DISP_DC_Pin GPIO_PIN_3
#define DISP_DC_GPIO_Port GPIOA
#define DISP_CS_Pin GPIO_PIN_4
#define DISP_CS_GPIO_Port GPIOA
#define NRF24_IRQ_Pin GPIO_PIN_0
#define NRF24_IRQ_GPIO_Port GPIOB
#define NRF24_CS_Pin GPIO_PIN_1
#define NRF24_CS_GPIO_Port GPIOB
#define NRF24_EN_Pin GPIO_PIN_2
#define NRF24_EN_GPIO_Port GPIOB
#define BTN_IRQ_Pin GPIO_PIN_10
#define BTN_IRQ_GPIO_Port GPIOB
#define BTN_1_Pin GPIO_PIN_11
#define BTN_1_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_12
#define BTN_2_GPIO_Port GPIOB
#define BTN_3_Pin GPIO_PIN_15
#define BTN_3_GPIO_Port GPIOB
#define BTN_4_Pin GPIO_PIN_8
#define BTN_4_GPIO_Port GPIOA
#define CLOCK_RST_Pin GPIO_PIN_8
#define CLOCK_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
