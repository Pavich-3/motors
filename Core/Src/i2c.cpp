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

	return HAL_OK;
}

HAL_StatusTypeDef I2C_Bus::writeDMA(uint8_t device_addr, uint8_t* data, uint16_t size)
{
	return HAL_I2C_Master_Transmit_DMA(i2cHandle, (device_addr << 1), data, size);
}

HAL_StatusTypeDef I2C_Bus::writeBlocking(uint8_t device_addr, uint8_t* data, uint16_t size, uint32_t timeout)
{
    return HAL_I2C_Master_Transmit(i2cHandle, (device_addr << 1), data, size, timeout);
}

void I2C_Bus::Error_Handler(void)
{
	__disable_irq();
	while (1)
	{

	}
}
