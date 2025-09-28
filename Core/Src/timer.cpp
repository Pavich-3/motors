#include <timer.hpp>

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

HAL_StatusTypeDef Timer_Init(TIM_HandleTypeDef* timerHandle)
{
	timerHandle->Instance = TIMER;
	timerHandle->Init.Prescaler = 15999;
	timerHandle->Init.Period = 9;
	timerHandle->Init.CounterMode = TIM_COUNTERMODE_UP;
	timerHandle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	timerHandle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(timerHandle) != HAL_OK) Error_Handler();

	return HAL_OK;
}
