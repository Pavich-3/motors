#include <main.h>

extern DMA_HandleTypeDef hdma_timer;
volatile uint32_t buffer = 0;

TIM_HandleTypeDef encoderHandle = {0};
TIM_HandleTypeDef timerHandle = {0};
TIM_HandleTypeDef pwmHandle = {0};
TIM_HandleTypeDef i2cHandle = {0};

void SystemClock_Config(void);

void HAL_DMA_CpltCallback(struct __DMA_HandleTypeDef * hdma)
{
    if (hdma->Instance == hdma_timer.Instance)
    {
        if (buffer > ENCODER_MAX)
            buffer = ENCODER_MAX;

        uint16_t new_pulse = SERVO_MIN_PULSE + (((uint32_t)buffer * (uint32_t)(SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / (uint32_t)ENCODER_MAX);

        __HAL_TIM_SET_COMPARE(&pwmHandle, TIM_CHANNEL_1, new_pulse);
    }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  Encoder_Init(&encoderHandle);
  Timer_Init(&timerHandle);
  PWM_Init(&pwmHandle);

  if (HAL_TIM_Encoder_Start(&encoderHandle, TIM_CHANNEL_ALL) != HAL_OK) Error_Handler();
  if (HAL_TIM_PWM_Start(&pwmHandle, TIM_CHANNEL_1) != HAL_OK) Error_Handler();

  if (HAL_DMA_RegisterCallback(&hdma_timer, HAL_DMA_XFER_CPLT_CB_ID, HAL_DMA_CpltCallback) != HAL_OK) Error_Handler();
  __HAL_TIM_ENABLE_DMA(&timerHandle, TIM_DMA_UPDATE);
  if (HAL_DMA_Start_IT(&hdma_timer, (uint32_t)&encoderHandle.Instance->CNT, (uint32_t)&buffer, 1) != HAL_OK) Error_Handler();


  if (HAL_TIM_Base_Start(&timerHandle) != HAL_OK) Error_Handler();

  __HAL_TIM_SET_COMPARE(&pwmHandle, TIM_CHANNEL_1, (uint16_t)((SERVO_MIN_PULSE + SERVO_MAX_PULSE) / 2.0f));


  while (1)
  {

  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
