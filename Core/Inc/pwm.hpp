#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

HAL_StatusTypeDef PWM_Init(TIM_HandleTypeDef* pwmHandle);

#ifdef __cplusplus
}
#endif

#endif
