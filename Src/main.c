
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "buzzerDriver.h"
#include "melody.h"


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  buzzerDriverInit();


  TIM2 -> CR1 |= TIM_CR1_CEN;
  TIM2 ->CCER |= TIM_CCER_CC4E;

  int melodyCount = sizeof(melodySizes)/ sizeof(uint32_t);

  for(int melodyIndex = 0; melodyIndex < melodyCount; melodyIndex++)
  {
	  for(int noteIndex = 0; noteIndex < melodySizes[melodyIndex]; noteIndex++)
  	  {
	  	  buzzerSetNewFrequency(melody[melodyIndex][noteIndex]);
	  	  HAL_Delay(noteDurations[melodyIndex][noteIndex] * melodySlowfactor[melodyIndex]);
  	  }
  }
   TIM2 -> CR1 &= ~TIM_CR1_CEN;
   TIM2 ->CCER &= ~TIM_CCER_CC4E;

  while (1)
  {

  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

/*****END OF FILE****/
