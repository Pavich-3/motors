#include <main.h>

DMA_HandleTypeDef hdma_timer = {0};
DMA_HandleTypeDef hdma_i2c = {0};

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
    if (i2cHandle->Instance == I2C1)
    {
        __HAL_RCC_I2C1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStruct = {
                .Pin = GPIO_PIN_6 | GPIO_PIN_7,
                .Mode = GPIO_MODE_AF_OD,
                .Pull = GPIO_PULLUP,
                .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
                .Alternate = GPIO_AF4_I2C1
        };
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        __HAL_RCC_DMA1_CLK_ENABLE(); // Переконайся, що тактування DMA увімкнене

        hdma_i2c.Instance = DMA1_Stream1; // Перевір свій Reference Manual, можливо потрібен інший стрім для I2C1_TX
        hdma_i2c.Init.Channel = DMA_CHANNEL_0; // Так само, перевір канал
        hdma_i2c.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_i2c.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_i2c.Init.MemInc = DMA_MINC_ENABLE;
        hdma_i2c.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_i2c.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_i2c.Init.Mode = DMA_NORMAL;
        hdma_i2c.Init.Priority = DMA_PRIORITY_LOW;
        hdma_i2c.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_i2c) != HAL_OK) Error_Handler();

        __HAL_LINKDMA(i2cHandle, hdmatx, hdma_i2c);
    }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance == PWM)
  {
	  __HAL_RCC_TIM1_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitSturct = {
			  .Pin = PWM_PIN,
			  .Mode = GPIO_MODE_AF_PP,
			  .Pull = GPIO_NOPULL,
			  .Speed = GPIO_SPEED_LOW,
			  .Alternate = GPIO_AF1_TIM1
	  };
	  HAL_GPIO_Init(PWM_PORT, &GPIO_InitSturct);
  }
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
	if (htim_encoder->Instance == ENCODER)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = {
				.Pin = ENCODER_CHANNEL_A | ENCODER_CHANNEL_B,
				.Mode = GPIO_MODE_AF_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_LOW,
				.Alternate = GPIO_AF1_TIM2
		};
		HAL_GPIO_Init(ENCODER_PORT, &GPIO_InitStruct);
	}
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (htim->Instance == TIMER)
  {
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	hdma_timer.Instance = DMA1_Stream2;
	hdma_timer.Init.Channel = DMA_CHANNEL_5;
	hdma_timer.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_timer.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_timer.Init.MemInc = DMA_MINC_DISABLE;
	hdma_timer.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_timer.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma_timer.Init.Mode = DMA_CIRCULAR;
	hdma_timer.Init.Priority = DMA_PRIORITY_LOW;
	if (HAL_DMA_Init(&hdma_timer) != HAL_OK) Error_Handler();

	__HAL_LINKDMA(htim, hdma[TIM_DMA_ID_UPDATE], hdma_timer);

	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  }
}

