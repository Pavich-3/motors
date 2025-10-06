#include <main.h>
#include <stm32f4xx_it.h>

extern DMA_HandleTypeDef hdma_timer;
extern I2C_HandleTypeDef i2cHandle;
extern DMA_HandleTypeDef hdma_i2c;

void DMA1_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_timer);
}

void DMA1_Stream1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_i2c);
}

void I2C1_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&i2cHandle);
}

void I2C1_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&i2cHandle);
}

void NMI_Handler(void)
{
   while (1)
  {

  }
}

void HardFault_Handler(void)
{
  while (1)
  {

  }
}

void MemManage_Handler(void)
{
  while (1)
  {

  }
}

void BusFault_Handler(void)
{
  while (1)
  {

  }
}

void UsageFault_Handler(void)
{
  while (1)
  {

  }
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void TIM2_IRQHandler(void)
{

}
