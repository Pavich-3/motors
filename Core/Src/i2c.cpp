#include <i2c.hpp>

extern DMA_HandleTypeDef hdma_i2c;

I2C_Bus::I2C_Bus(I2C_HandleTypeDef* i2cHandle) : i2cHandle(i2cHandle) {}

HAL_StatusTypeDef I2C_Bus::i2cInit(void)
{
	i2cHandle->Instance = I2C1;
	i2cHandle->Init.ClockSpeed = 400000;
	i2cHandle->Init.DutyCycle = I2C_DUTYCYCLE_2;
	i2cHandle->Init.OwnAddress1 = 0;
	i2cHandle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2cHandle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2cHandle->Init.OwnAddress2 = 0;
	i2cHandle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2cHandle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(i2cHandle) != HAL_OK) this->Error_Handler();
}

HAL_StatusTypeDef I2C_Bus::i2cMspInit(void)
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

			hdma_i2c.Instance = DMA1_Stream1;
			hdma_i2c.Init.Channel = DMA_CHANNEL_0;
			hdma_i2c.Init.Direction = DMA_MEMORY_TO_PERIPH;
			hdma_i2c.Init.PeriphInc = DMA_PINC_DISABLE;
			hdma_i2c.Init.MemInc = DMA_MINC_ENABLE;
			hdma_i2c.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
			hdma_i2c.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
			hdma_i2c.Init.Mode = DMA_CIRCULAR;
			hdma_i2c.Init.Priority = DMA_PRIORITY_LOW;
			hdma_i2c.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
			hdma_i2c.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
			if (HAL_DMA_Init(&hdma_i2c) != HAL_OK) this->Error_Handler();

			__HAL_LINKDMA(i2cHandle, hdmarx, hdma_i2c);
		}
}

HAL_StatusTypeDef I2C_Bus::write(uint8_t device_addr, uint8_t* data, uint16_t size)
{
	return HAL_I2C_Master_Transmit_DMA(i2cHandle, (device_addr << 1), data, size);
}

void I2C_Bus::Error_Handler(void)
{
	__disable_irq();
	while (1)
	{

	}
}
