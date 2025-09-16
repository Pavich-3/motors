#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

HAL_StatusTypeDef Timer_Init(TIM_HandleTypeDef* timerHandle);

#ifdef __cplusplus
}
#endif
#endif
