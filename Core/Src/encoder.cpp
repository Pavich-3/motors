#include <encoder.hpp>

HAL_StatusTypeDef Encoder_Init(TIM_HandleTypeDef *timHandle)
{
	timHandle->Instance = ENCODER;
	timHandle->Init.Prescaler = 0;
	timHandle->Init.Period = ENCODER_MAX;
	timHandle->Init.CounterMode = TIM_COUNTERMODE_UP;
	timHandle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	TIM_Encoder_InitTypeDef sConfig = {
		.EncoderMode = TIM_ENCODERMODE_TI12,
		.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING,
		.IC1Selection = TIM_ICSELECTION_DIRECTTI,
		.IC1Prescaler = TIM_ICPSC_DIV1,
		.IC1Filter = 1,
		.IC2Polarity = TIM_INPUTCHANNELPOLARITY_RISING,
		.IC2Selection = TIM_ICSELECTION_DIRECTTI,
		.IC2Prescaler = TIM_ICPSC_DIV1,
		.IC2Filter = 1
	};
	if (HAL_TIM_Encoder_Init(timHandle, &sConfig) != HAL_OK) Error_Handler();

	return HAL_OK;
}
