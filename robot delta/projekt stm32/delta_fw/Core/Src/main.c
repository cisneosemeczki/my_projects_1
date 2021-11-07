/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "stepper.h"
#include "interpolation.h"
#include "uart_protocol.h"
#include "delta_kinematics.h"
#include "limit_switch.h"

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

int robot_w_trakcie_ruchu;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin == X_MIN_Pin || X_MAX_Pin || Y_MIN_Pin || Y_MAX_Pin || Z_MIN_Pin || Z_MAX_Pin){
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		Stepper_EndStopHandler();
	}
	if (GPIO_Pin == USER_BUTTON_Pin){
		stan = 1;
	}
}
*/

void skalowanie(punkt_kartezjanski *wyskalowany,
				punkt_kartezjanski *pt_str,
				punkt_kartezjanski *pt_kon)
{
	float droga_do_przebycia_x = (pt_kon->x - pt_str->x) * 0.326797F * 1.063830F;
	float droga_do_przebycia_y = (pt_kon->y - pt_str->y) * 0.543478F * 1.204819F;  //1.155942F
	float droga_do_przebycia_z = (pt_kon->z - pt_str->z) * 1.250000F * 1.086957F;

	wyskalowany->x = pt_str->x + droga_do_przebycia_x;
	wyskalowany->y = pt_str->y + droga_do_przebycia_y;
	wyskalowany->z = pt_str->z + droga_do_przebycia_z;

	//printf("wyskalowany: X: %.3f   Y: %.3f   Z: %.3f\n", wyskalowany->x, wyskalowany->y, wyskalowany->z);
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  Stepper_Disable(&lista_silnikow[0]);
  Stepper_Disable(&lista_silnikow[1]);
  Stepper_Disable(&lista_silnikow[2]);

  robot_w_trakcie_ruchu = 0;
  kalibracja_wykonana = 0;

  punkt_kartezjanski punkt_startowy = {};
  punkt_kartezjanski punkt_koncowy = {};

  punkt_startowy.x = 0;
  punkt_startowy.y = 0;
  punkt_startowy.z = 0;

  Stepper_Init();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  uint8_t value;
	  if (HAL_UART_Receive(&huart2, &value, 1, 0) == HAL_OK)
		  odbior_danych_z_aplikacji(value);
/*
	  if (stan1 == 1)
	  	  {

	  		  float lengths[3] = { 0 };

	  		  int res = 1;
	  		  punkt_kartezjanski p_str = {};
	  		  punkt_kartezjanski p_end = {};

	  		  p_str.x = 0;
	  		  p_str.y = 0;
	  		  p_str.z = 0;

	  		  p_end.x = 0;
	  		  p_end.y = 0;
	  		  p_end.z = -20;

	  		  lista_silnikow[0].absPos = -361.263702;
	  		  lista_silnikow[1].absPos = -415.196625;
	  		  lista_silnikow[2].absPos = -415.196625;


	  		  //Stepper_Init();

	  		  //kalibracja_krancowek();

	  		  //while(kalibracja_wykonana != 1) {}



	  		  liniowa_interpolacja(p_str, p_end, res, 50, 100);

	  		  Stepper_Init();
	  		  //Stepper_EnableAll();

	  		  //Stepper_moveAbsPos(&sList[2], 440, 4);


	  		  for (uint8_t i = 1; i <= res; i++)
	  		  {
	  			  odwrotna_kinematyka(lengths, trajektoria_liniowa[i].wektor);

	  			  Stepper_EnableAll();

	  		  	  Stepper_moveAbsPos(&lista_silnikow[0], lengths[0], 13);    //(sList[0].absPos - lengths[0]) / traj_lin[i].t)

	  		  	  Stepper_moveAbsPos(&lista_silnikow[1], lengths[1], 13);

	  		  	  Stepper_moveAbsPos(&lista_silnikow[2], lengths[2], 13);
	  		  	  while(lista_silnikow[0].moving_f == 1) {}
	  		  	  while(lista_silnikow[1].moving_f == 1) {}
	  		  	  while(lista_silnikow[2].moving_f == 1) {}
	  		  	  //while(lista_silnikow[0].moving_f == 1 || lista_silnikow[1].moving_f == 1 || lista_silnikow[2].moving_f == 1) {}

	  		  }

	  		  stan1 = 0;
	  	  }
*/


	  //glowny program
	  if (stan1 == 1)
	  {
		  //kalibracja_krancowek();

		  //punkt_startowy.x = 0;
		  //punkt_startowy.y = 0;
		  //punkt_startowy.z = 0;

		  //while(kalibracja_wykonana != 1) {}

		  lista_silnikow[0].absPos = -361.263702;
		  lista_silnikow[1].absPos = -415.196625;
		  lista_silnikow[2].absPos = -415.196625;

		  kalibracja_wykonana = 1;

		  stan1 = 0;
	  }

	  if (ruch_robotem == 1 && podczas_kalibracji == 0 && kalibracja_wykonana == 1 && robot_w_trakcie_ruchu == 0)
	  {
		  robot_w_trakcie_ruchu = 1;

		  float lengths_przeskalowane[3] = { 0 };
		  float lengths[3] = { 0 };

		  punkt_koncowy.x = wspolrzedna_X;
		  punkt_koncowy.y = wspolrzedna_Y;
		  punkt_koncowy.z = wspolrzedna_Z;

		  int rozdzielczosc = rozdzielczosc_interpolacji;

		  if (punkt_startowy.x == punkt_koncowy.x && punkt_startowy.y == punkt_koncowy.y && punkt_startowy.z == punkt_koncowy.z)
		  {
			  printf("Efektor sie nie przemiesci bo podano punkt, w ktorym sie znajduje teraz!\n");
			  robot_w_trakcie_ruchu = 0;
			  ruch_robotem = 0;
			  continue;
		  }


		  punkt_kartezjanski wyskalowany_punkt_koncowy = {};
		  skalowanie(&wyskalowany_punkt_koncowy, &punkt_startowy, &punkt_koncowy);


		  if (rodzaj_interpolacji == 1)
		  {

			  liniowa_interpolacja(punkt_startowy, wyskalowany_punkt_koncowy, rozdzielczosc, 50, 100);

			  for (int i = 1; i <= rozdzielczosc; i++)
			  {
				  odwrotna_kinematyka(lengths_przeskalowane, trajektoria_liniowa[i].wektor);

				  float diff_lengths1 = (lengths_przeskalowane[1] - lista_silnikow[1].absPos) * 0.893;
				  float diff_lengths2 = (lengths_przeskalowane[2] - lista_silnikow[2].absPos) * 0.893;
				  lengths_przeskalowane[1] = lista_silnikow[1].absPos + diff_lengths1;
				  lengths_przeskalowane[2] = lista_silnikow[2].absPos + diff_lengths2;

				  Stepper_EnableAll();										//(sList[0].absPos - lengths[0]) / traj_lin[i].t)

			  	  Stepper_moveAbsPos(&lista_silnikow[0], lengths_przeskalowane[0], 13);
			  	  Stepper_moveAbsPos(&lista_silnikow[1], lengths_przeskalowane[1], 13);
			  	  Stepper_moveAbsPos(&lista_silnikow[2], lengths_przeskalowane[2], 13);

			  	  while(lista_silnikow[0].moving_f == 1 || lista_silnikow[1].moving_f == 1 || lista_silnikow[2].moving_f == 1) {}

			  }
		  }
		  else if (rodzaj_interpolacji == 2)
		  {
			  przegubowa_interpolacja(punkt_startowy, wyskalowany_punkt_koncowy, rozdzielczosc, 50, 100);

			  for (int i = 1; i <= rozdzielczosc; i++)
			  {
				  odwrotna_kinematyka(lengths_przeskalowane, droga_przegubowa[i].wektor);

				  float diff_lengths1 = (lengths_przeskalowane[1] - lista_silnikow[1].absPos) * 0.893;
				  float diff_lengths2 = (lengths_przeskalowane[2] - lista_silnikow[2].absPos) * 0.893;
				  lengths_przeskalowane[1] = lista_silnikow[1].absPos + diff_lengths1;
				  lengths_przeskalowane[2] = lista_silnikow[2].absPos + diff_lengths2;

				  Stepper_EnableAll();

			  	  Stepper_moveAbsPos(&lista_silnikow[0], lengths_przeskalowane[0], 13);
			  	  Stepper_moveAbsPos(&lista_silnikow[1], lengths_przeskalowane[1], 13);
			  	  Stepper_moveAbsPos(&lista_silnikow[2], lengths_przeskalowane[2], 13);

			  	  while(lista_silnikow[0].moving_f == 1 || lista_silnikow[1].moving_f == 1 || lista_silnikow[2].moving_f == 1) {}
			  }
		  }
		  else if (rodzaj_interpolacji == 3)
		  {
			  kolowa_interpolacja(punkt_startowy, wyskalowany_punkt_koncowy, 40, rozdzielczosc, 50, 100);
			  for (int i = 1; i <= rozdzielczosc; i++)
			  {
				  odwrotna_kinematyka(lengths_przeskalowane, trajektoria_kolowa[i].wektor);

				  float diff_lengths1 = (lengths_przeskalowane[1] - lista_silnikow[1].absPos) * 0.893;
				  float diff_lengths2 = (lengths_przeskalowane[2] - lista_silnikow[2].absPos) * 0.893;
				  lengths_przeskalowane[1] = lista_silnikow[1].absPos + diff_lengths1;
				  lengths_przeskalowane[2] = lista_silnikow[2].absPos + diff_lengths2;

				  Stepper_EnableAll();

				  Stepper_moveAbsPos(&lista_silnikow[0], lengths_przeskalowane[0], 7);
				  Stepper_moveAbsPos(&lista_silnikow[1], lengths_przeskalowane[1], 7);
				  Stepper_moveAbsPos(&lista_silnikow[2], lengths_przeskalowane[2], 7);

				  while(lista_silnikow[0].moving_f == 1 || lista_silnikow[1].moving_f == 1 || lista_silnikow[2].moving_f == 1) {}
			  }
		  }
		  odwrotna_kinematyka(lengths, punkt_koncowy.wektor);
		  lista_silnikow[0].absPos = lengths[0];
		  lista_silnikow[1].absPos = lengths[1];
		  lista_silnikow[2].absPos = lengths[2];

		  punkt_startowy.x = wspolrzedna_X;
		  punkt_startowy.y = wspolrzedna_Y;
		  punkt_startowy.z = wspolrzedna_Z;

		  robot_w_trakcie_ruchu = 0;
		  ruch_robotem = 0;
	  }
	  else
	  {
		  ruch_robotem = 0;
	  }



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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
