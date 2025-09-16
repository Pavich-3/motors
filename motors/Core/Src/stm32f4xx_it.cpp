#include <main.h>
#include "stm32f4xx_it.h"

extern DMA_HandleTypeDef hdma_timer;

void DMA1_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_timer);
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

void I2C1_EV_IRQHandler(void)
{

}
void I2C1_ER_IRQHandler(void)
{

}

void DMA2_Stream1_IRQHandler(void)
{

}
