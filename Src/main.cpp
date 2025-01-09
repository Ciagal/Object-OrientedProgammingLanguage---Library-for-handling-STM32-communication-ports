#include "main.h"
#include "CommunicationLib.hpp"
#include "usart.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"
#include <cstring>
#include <cstdio>
#include <stdio.h>
void SystemClock_Config(void);

#define TEST_UART
//#define TEST_SPI
//#define TEST_I2C

int main(void) {

	// HAL and SySClockInit;
	HAL_Init();
    SystemClock_Config();

    // GPIO INIT
    MX_GPIO_Init();


#ifdef TEST_UART
	MX_USART2_UART_Init();
    MC::UARTHandler uartHandler(&huart2, HAL_MAX_DELAY);
    uartHandler.init();
    //alternative
    //UARTHandler uartDefaultHandler;
    //uartDefaultHandler.setConfig(&huart2);
    uint8_t message[] = "Tesciczek\n";
    while (1) {
    	uartHandler.transmit(0, message, sizeof(message));
    	HAL_Delay(1000);
    }

#endif

#ifdef TEST_I2C
    	MX_USART2_UART_Init();
		MX_I2C1_Init();
	   	MC::UARTHandler uartHandler(&huart2, HAL_MAX_DELAY);
	   	MC::I2CHandler i2cHandler(&hi2c1, HAL_MAX_DELAY);
	   	uartHandler.init();
	   	i2cHandler.init();
    	MC::SHT35 sht35(&i2cHandler);

    	    float temperature = 0.0f;
    	    float humidity = 0.0f;

    	    while (1) {
    	    	sht35.read(temperature, humidity);
    	       	char buffer[50];
    	        snprintf(buffer, sizeof(buffer), "Temp: %.2f C, Hum: %.2f %%\n", temperature, humidity);
    	        uartHandler.transmit(0, reinterpret_cast<const uint8_t*>(buffer), strlen(buffer));
    	        HAL_Delay(1000); // delay 1s
    	    }
#endif


#ifdef TEST_SPI
    	MX_USART2_UART_Init();
		MX_SPI1_Init();
	   	MC::UARTHandler uartHandler(&huart2, HAL_MAX_DELAY);
	   	MC::SPIHandler spiHandler(&hspi1, HAL_MAX_DELAY);
	   	uartHandler.init();
	   	spiHandler.init();

	   	MC::BME280 bme280(&spiHandler, GPIOC, GPIO_PIN_13);
	   	bme280.initialize();

	   	while (1) {
	   	     //read
	   	     float temperature = bme280.readTemperature();


	   	     char buffer[100];
	   	     snprintf(buffer, sizeof(buffer), "Temp: %.2f C", temperature);
	   	     uartHandler.transmit(0, reinterpret_cast<uint8_t*>(buffer), strlen(buffer));

	   	     HAL_Delay(1000); // delay 1s
	   	 }

#endif
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


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
