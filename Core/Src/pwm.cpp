#include <pwm.hpp>

HAL_StatusTypeDef PWM_Init(TIM_HandleTypeDef* pwmHandle)
{
	pwmHandle->Instance = PWM;
	pwmHandle->Init.Period = 999;
	pwmHandle->Init.Prescaler = 319;
	pwmHandle->Init.CounterMode = TIM_COUNTERMODE_UP;
	pwmHandle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	pwmHandle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_PWM_Init(pwmHandle) != HAL_OK) Error_Handler();

	TIM_OC_InitTypeDef sConfigOC = {
			.OCMode = TIM_OCMODE_PWM1,
			.Pulse = 0,
			.OCPolarity = TIM_OCPOLARITY_HIGH,
			.OCFastMode = TIM_OCFAST_DISABLE
	};
	if (HAL_TIM_PWM_ConfigChannel(pwmHandle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) Error_Handler();

	return HAL_OK;
}
