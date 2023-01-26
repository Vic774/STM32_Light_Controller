/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_config.h"
#include "bh1750_config.h"
#include "pid_config.h"
#include "menu_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t Received[10];
//char str_buffer[16];
float pulse = 0;
int int_pulse, int_Light, int_LightSetpoint;
double Light, PID_Out, LightSetpoint;
char send_buffer[150];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void send_string(char* s)
{
	HAL_UART_Transmit_IT(&huart3, (uint8_t*)s, strlen(s));
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback ( uint16_t GPIO_Pin )
{
	if(GPIO_Pin == Back_Btn_Pin)
	{
		if(hmenu.Item->Parent != NULL)
		{
			hmenu.Item = hmenu.Item->Parent;
			hmenu.ItemChanged = 1;
		}
	}
	else if(GPIO_Pin == Up_Btn_Pin)
	{
		if(hmenu.Item->Next != NULL)
		{
			hmenu.Item = hmenu.Item->Next;
			hmenu.ItemChanged = 1;
		}
	}
	else if(GPIO_Pin == Next_Btn_Pin)
	{
		if(hmenu.Item->Child != NULL)
		{
			hmenu.Item = hmenu.Item->Child;
			hmenu.ItemChanged = 1;
		}
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM3)
  {
	  static int time_ms2 = 0;

	  MENU_ROUTINE(&hmenu);

	  if(time_ms2 % 1000 == 0)
	  {
		  int_LightSetpoint = (int)LightSetpoint;
		  sprintf(send_buffer, "*****\n\nLight set value: %4d [lx]\nCurrent value: %4d [lx]\nController Signal: %2.1f [%%]\n\n", int_LightSetpoint, int_Light, PID_Out/10);
		  send_string(send_buffer);
	  }

	  time_ms2 += 500;
	  if(time_ms2 == 3000)
	  {
		  time_ms2 = 0;
	  }
  }

  if (htim->Instance == TIM6)
    {
	  static int time_ms = 0;

	  if(time_ms % 20 == 0)
	  {
		  Light = BH1750_ReadLux(&hbh1750_1);
		  int_Light = (int)Light;

		  PID_Compute(&Light_PID);

		  int_pulse = (int)PID_Out;
		  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, int_pulse);
	  }

	  time_ms += 20;
	  if(time_ms == 1000)
	  {
		  time_ms = 0;
	  }
    }


}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t Data[6];
	sprintf(Data, "%s",Received);
	if(Data[0]=='L')
	{
		int value = atoi(&Data[1]);
		if(value >= 0 && value <=9999)
		{
			char send_buffer[32];
			LightSetpoint = value;

			sprintf(send_buffer, "Light: %4d [lx]\r\n", value);
			send_string(send_buffer);
		}
	}
	if(Data[0]=='M')
	{
		if(!strncmp( Data, "MNext", 5 ) && hmenu.Item->Next != NULL)
		{
			hmenu.Item = hmenu.Item->Next;
			hmenu.ItemChanged = 1;
		}
		if(!strncmp( Data, "MPrev", 5 ) && hmenu.Item->Prev != NULL)
		{
			hmenu.Item = hmenu.Item->Prev;
			hmenu.ItemChanged = 1;
		}
		if(!strncmp( Data, "MChld", 5 ) && hmenu.Item->Child != NULL)
		{
			hmenu.Item = hmenu.Item->Child;
			hmenu.ItemChanged = 1;
		}
		if(!strncmp( Data, "MPrnt", 5 ) && hmenu.Item->Parent != NULL)
		{
			hmenu.Item = hmenu.Item->Parent;
			hmenu.ItemChanged = 1;
		}
	}
	HAL_UART_Receive_IT(&huart3, Received, 5);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  MX_TIM14_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  BH1750_Init(&hbh1750_1);
  Lcd_init(&lcd);

  LightSetpoint = 200;
  PID(&Light_PID, &Light, &PID_Out, &LightSetpoint, 0.2, 10, 0, _PID_P_ON_E, _PID_CD_DIRECT);

  PID_SetMode(&Light_PID, _PID_MODE_AUTOMATIC);
  PID_SetSampleTime(&Light_PID, 20);
  PID_SetOutputLimits(&Light_PID, 0, 999);

  MENU_Init(&hmenu);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_UART_Receive_IT(&huart3, Received, 5);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
